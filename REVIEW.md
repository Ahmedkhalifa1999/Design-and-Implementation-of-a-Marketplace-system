# Codebase Review: Marketplace System

Review date: 2026-09-18
Scope: everything on `main` at commit `91882ac` ("Final 2"), both `Marketplace-Server` (Java) and `Marketplace-Client` (Qt/C++), the SQL dumps, and the repository itself.
Method: full read of all source, then a build of both halves on Ubuntu 24.04, a live run of the server against MariaDB with the shipped seed data, and a protocol-level test client that exercised every request ID. Findings marked **[verified]** were reproduced against the running system; findings marked **[by reading]** are from code inspection only.

---

## 1. Verdict

The project has a sensible skeleton: a Java TCP server speaking JSON, a Qt desktop client, a MySQL schema, and a documented request/response ID scheme. Both halves compile. The server starts and answers simple requests.

Beyond that skeleton, the core business flows do not work, and several of them fail in ways that would be dangerous in a real marketplace:

- A customer with 100.50 EGP successfully ordered a 240.00 EGP phone. Stock was decremented, an order row was written, and the wallet was never charged. **[verified]**
- The checkout response reports availability and funds with inverted meaning, so the client shows "item unavailable" when the real problem is money, and vice versa. **[verified]**
- Order history and order details crash the connection for any user who actually has orders, because the SQL reads columns that are not in the `SELECT`. **[verified]**
- The Qt client sends a payload for checkout and cart retrieval that the server cannot parse (a bare JSON array instead of an object), so neither flow can ever succeed from the real client. **[verified against the server with the exact bytes the client builds]**
- The client's password "hashing" runs SHA3 output through `QString::fromUtf8`, which destroys roughly a third of the hash bytes. None of the nine seeded users can log in from the client, because the seed data stores plaintext passwords. **[verified by running the client's exact code]**
- The server has no authentication state beyond a per-connection email field. Every catalogue request, and the wallet-deposit path, is reachable without logging in. **[verified]**
- The "asynchronous" server blocks one pool thread per connection. The ninth simultaneous client hangs until one of the first eight disconnects. **[verified]**
- Any malformed, oversized, coalesced, or unexpected request kills the handler thread with an uncaught exception and leaves the socket open, so the client hangs forever with no error. **[verified, nine distinct triggers]**

The repository itself is 428 MB and 1,538 files, of which 1,372 are tracked build artifacts (object files, DLLs, executables, IDE caches, a 53 MB fat jar, and an entire Windows JavaFX SDK). The database root password and several developers' home-directory paths are committed in source.

For a course project built under deadline pressure (the commit history literally counts down: "6 hours remaining", "3 hours remaining", "1 hour remaining", "Final", "Final 2"), the ambition is reasonable. As a codebase to build on, it needs the fixes in section 8 before anything else.

---

## 2. What the system is

```
+---------------------------+        TCP 28142, JSON, no framing        +---------------------------+
|  Marketplace-Client (Qt6) | <---------------------------------------> |  Marketplace-Server (Java) |
|  MainWindow / Login /     |                                           |  Server (accept loop)      |
|  Shop / Itemdet / Cart /  |                                           |  ClientHandler x8 threads  |
|  Account                  |                                           |  DataManager               |
|  DataManager (socket,     |                                           |  DatabaseManager (JDBC)    |
|   JSON, local cart file)  |                                           |  AdminPanel (JavaFX)       |
+---------------------------+                                           +-------------+-------------+
                                                                                      | JDBC, root/hardcoded pw
                                                                                +-----v-----+
                                                                                |  MySQL     |
                                                                                | customer   |
                                                                                | items      |
                                                                                | orders     |
                                                                                | orderitem  |
                                                                                +-----------+
```

- **Protocol.** Each request is a JSON object with an integer `ID`. Even IDs are requests (0 register, 2 login, 4 checkout, 6 account, 8 update account, 10 order history, 12 order details, 14 deposit, 16 item list, 18 item data, 20 categories, 22 cart items). The response uses `ID + 1`. Item icons travel inline as base64 JPEG.
- **Server.** `Server` accepts on an `AsynchronousServerSocketChannel` and hands each connection to a `ClientHandler` running on a fixed pool of 8 threads. `ClientHandler` dispatches on `ID` to `DataManager`, which holds the connection's identity (`email`) and delegates all persistence to static methods in `DatabaseManager`. `AdminPanel` is a JavaFX window with "Import Report" and "Add Items" buttons.
- **Client.** `DataManager` owns the `QTcpSocket`, serialises requests, and on `readyRead` parses the response and emits a typed Qt signal. Each dialog connects to the signals it cares about. The shopping cart is a local JSON file (`cart_data.txt`), not server state.
- **Data.** Four tables. Money is stored as an `int` in piasters and split into pounds/piasters at the edges.

Source size is small: about 1,460 lines of Java and 3,500 lines of C++/`.ui`.

---

## 3. Build and run report

| Step | Result | Notes |
|---|---|---|
| Compile Java server (JDK 21, `javac -Xlint:all` against `lib/*.jar`) | Success | 20 warnings: 19 redundant casts, one `this-escape` in `ClientHandler`'s constructor. Sources use records and arrow-switch, so JDK 16+ is required; IntelliJ config says 18, README says nothing. |
| Load SQL dumps into MariaDB 10.11 | Failed, then fixed | Dumps specify `utf8mb4_0900_ai_ci`, a MySQL 8-only collation. Loaded after substituting `utf8mb4_unicode_ci`. Dumps are per-table and must be loaded in FK order (customer, items, orders, orderitem); nothing documents this and there is no `CREATE DATABASE`. |
| Run server | Success, with caveats | Must be launched from the repository root, because `DatabaseManager.getIcon` uses the relative path `Marketplace-Server/database/icons`. OpenJFX had to be supplied separately; the bundled JavaFX jars are the Windows builds. Admin panel opened on Xvfb. |
| Compile Qt client (`qmake6` + `make`, Qt 6.4.2, `-Wall -Wextra`) | Success | Zero warnings. Credit where due. |
| Run Qt client (offscreen platform) against server | Starts, connects, stays up | Interactive flows were exercised via a protocol client instead, because the GUI cannot be driven headlessly here. |
| Protocol test: 12 request types, malformed input, concurrency | See section 5 | 9 of the probes killed the handler thread server-side. |

Environment set-up needed to get here, none of which is documented in the repo: install MariaDB, set the root password to the value hardcoded in `DatabaseManager.java`, create the `marketplace` database, patch the collation, install OpenJFX for Linux, install Qt 6 dev packages, run from the right directory.

---

## 4. Findings: security

### S1. Database root password and developer machine paths committed in source. [verified]
`Marketplace-Server/src/DatabaseManager.java:14-20` and `:626`. The server connects as MySQL `root` with a literal password that has been in the history since commit `914e09e`. Two different developers' `C:\Users\...` paths are hardcoded, one of them inside a method body. Rotate the password, move connection settings to environment variables or a config file outside the repo, and create a least-privilege DB user.

### S2. No authentication or session model. [verified]
Identity is a single `email` field on the connection's `DataManager`, set by a successful login *or by any registration attempt*. Consequences observed:
- Catalogue, item detail, and cart-lookup requests (16, 18, 20, 22) work with no login at all.
- `{"ID":6}` with no login returns an empty account object instead of an error.
- `{"ID":14, ...}` (deposit) with no login returns `"Result": true`. It updates zero rows, but the client is told it succeeded.
- `register()` in `DataManager.java:131-140` sets `this.email` before knowing whether the insert succeeded. After the 100-character-name registration below, the connection was "logged in" as a user that does not exist.
- There is no logout and no way to bind a request to a user other than by which TCP connection it arrived on.

### S3. Password handling is broken on both ends. [verified]
- Client (`datamanager.cpp:80-86`, `:116-122`): SHA3-256 is computed, then the 32 raw bytes are passed through `QString::fromUtf8`. Invalid UTF-8 sequences become U+FFFD. Running that exact code on the four sample passwords lost 9 to 13 of the 32 bytes each. The value put on the wire is a 30-32 character string of mostly replacement characters and control codes, no salt, no encoding. This is not a hash, it is a lossy transform of one.
- Server (`DatabaseManager.java:322-347`): stores whatever string arrives in `varchar(50)` and compares with `WHERE email = ? AND password = ?`. No hashing, no salt, no constant-time comparison.
- Seed data (`marketplace_customer.sql`): all nine passwords are plaintext (`bassantyasser`, `caty`, `admin`, ...). The Qt client can therefore never log in as any seeded user, since it will always send the mangled SHA3 form.

### S4. Unbounded and unvalidated money operations. [verified]
`{"ID":14,"Amount":{"Pounds":-1000,"Piasters":0}}` was accepted and left the wallet at `-987.50`. `{"Pounds":10,"Piasters":250}` was also accepted (piasters is not bounded to 0-99). `updateWallet` in `DatabaseManager.java:518-535` does `wallet = wallet + ?` with no sign or range check, and `int temp` can overflow for large inputs.

### S5. Plaintext, unauthenticated, unframed TCP. [by reading]
No TLS, no message length prefix, no request authentication. Anyone on the network path can read or replay every request, including credentials.

### S6. What is done right.
Every SQL statement uses `PreparedStatement` with bound parameters. I found no SQL injection path. The email/phone regex validation on the client (`datamanager.cpp:28-50`) is reasonable for what it is.

---

## 5. Findings: server correctness

Each row below was reproduced with the protocol client. "Thread died" means an uncaught `RuntimeException` terminated the pool thread; the server never writes a response and never closes the socket, so the client blocks forever.

| # | Trigger | Observed | Root cause |
|---|---|---|---|
| C1 | `{"ID":10}` for a user who has orders | Thread died: `SQLException: Column 'ID' not found` then NPE | `DatabaseManager.java:127` reads `rs.getInt("ID")`; the column is `orderid`. Even if fixed, `:134` calls `res.set(i, ...)` on an empty `ArrayList`, which throws `IndexOutOfBoundsException`. Users with zero orders get `[]`, which is why it looked like it worked. |
| C2 | `{"ID":12,"Order ID":3}` | Thread died: `Column 'oi.itemid' not found` then NPE | `DatabaseManager.java:198` reads `oi.itemid`, which is not in the `SELECT` list at `:185`. Additionally, `ClientHandler.java:180-182` builds the order total JSON and never attaches it, and never sends `State`, both of which the client reads. |
| C3 | Checkout: weza (100.50) buys item 4 (240.00) | `"Funds": true`, order 5 inserted, stock 2 to 1, **wallet still 100.50** | `DataManager.java:187` compares `(pou/100) + pia` against the same nonsense for the wallet. For 240 pounds that is `2 + 0 = 2`, and 100.50 becomes `1 + 50 = 51`, so 2 <= 51 passes. The correct comparison is `pou*100 + pia`. Separately, nothing in `checkout()` ever debits the wallet. |
| C4 | Checkout: breksam (100.00) buys item 6 (0.15) | `"Funds": false`, order refused | Same arithmetic: `0 + 15 = 15 > 1 + 0 = 1`. A customer with 100 pounds cannot buy a 15-piaster item. |
| C5 | Any checkout | Response field semantics inverted | `DataManager.java:201` builds `CheckoutResult(flag1, flag2, out)` where `flag1` means "all available" and `flag2` means "enough funds", but the record fields are `unavailableItem` and `notEnoughFunds`. `ClientHandler` forwards them as `Unavailable` and `Funds`. The client then shows "Item of ID X is unavailable" on an out-of-funds order. |
| C6 | `{"ID":16, "Categories":["clothes","Mobiles"]}` | 2 items returned; DB has 6 in those categories | `DatabaseManager.java:159-171`: the `while (rs.next())` loop overwrites local variables and the `res.add` is *after* the loop, so only the last row per category survives. `Max Results` and the search term are otherwise honoured. |
| C7 | Same request | Response was 202,887 bytes for 2 items | Icons are base64 JPEGs inlined in every list response. With C6 fixed, a 10-item page would be around 1 MB per category. No caching, no separate image endpoint, no thumbnails. |
| C8 | Two requests arriving in one TCP segment | Thread died: `MalformedJsonException` | No message framing. `ClientHandler.java:59-70` reads one 2048-byte buffer and parses whatever is in it as exactly one JSON document. TCP does not preserve message boundaries; this also happened spontaneously during testing when the server was slow writing a large response. |
| C9 | Request larger than 2048 bytes (120-line cart, 3,739 bytes) | Thread died: `Unterminated string at column 2049` | Same fixed buffer. Any real cart, or any request with a long address, will hit this. |
| C10 | Register user with Arabic name, then `{"ID":6}` | Thread died: `BufferOverflowException` | `ClientHandler.java:282-283` allocates `response.length()` bytes (UTF-16 code units) and writes `response.getBytes()` (UTF-8 bytes). Any non-ASCII character in any response overflows. |
| C11 | Real Qt client checkout payload `[{"ID":1,"Quantity":1}]` | Thread died: `Not a JSON Object` | See client finding K1; the server also has no guard for a non-object root. |
| C12 | `{"ID":2}` (missing fields) | Thread died: NPE | `requestObject.get("Email")` returns null; every field access in the switch assumes presence. |
| C13 | `hello server` (not JSON) | Thread died | Same parse path. |
| C14 | `{"ID":999}` | `{}` | Unknown IDs return an empty object rather than an error. |
| C15 | Client disconnects | Thread died: `NegativeArraySizeException: -1` | `ClientHandler.java:62-64`: `read()` returns -1 at EOF and the code does `new byte[-1]`. The socket is never closed on the server side. |
| C16 | Register with a 100-character name (`name` is `varchar(45)`) | `"Result": true`; no row exists | `DatabaseManager.addRegister` catches `MysqlDataTruncation`, prints it, returns `void`; `DataManager.register` returns `true` regardless. Every `DatabaseManager` write method has this shape: exceptions are printed and swallowed, and callers cannot tell. |
| C17 | 8 idle connections open, 9th sends a request | 9th hangs until one of the 8 closes | `Server.java:19` fixed pool of 8; `ClientHandler.run` loops forever per connection with blocking `.get()` on every async future. The `AsynchronousSocketChannel` API is used fully synchronously, so the design has the cost of async and the scalability of one-thread-per-connection capped at 8. `ClientHandler`'s constructor also calls `socket.get()` on the accept thread, serialising accepts. |
| C18 | Three item-list requests | 7 idle JDBC connections left open on the DB | `DatabaseManager.item_list` (`:150`) opens one connection per category inside the loop and never closes any of them. Other methods close only on the happy path (no try-with-resources). MySQL's default `max_connections` is 151, so the server will stop working after roughly 75 two-category searches. |

Further server issues found by reading:

- **C19. Non-transactional checkout.** Stock decrement, order insert, and order-item inserts are separate autocommit statements on separate connections (`DataManager.java:190-199`, `DatabaseManager.java:401-455`). A failure part way through leaves stock decremented with no order, or an order with no items. The static `mutex` serialises checkouts within one JVM but does not make them atomic.
- **C20. Manual primary keys.** `addOrder` and `add_item` do `SELECT max(id)` then insert `max+1`. Neither `orders.orderid` nor `items.itemid` is `AUTO_INCREMENT`. Two servers, or the admin panel and a checkout at the same moment, will collide.
- **C21. Seed data violates the enum.** `orders.state` contains `'arrived'`, but `OrderState` is `ACCEPTED, SHIPPING, SHIPPED, REJECTED`. Once C1 is fixed, `OrderState.valueOf("arrived")` will throw for breksam's history.
- **C22. Item details are stubs.** `item_details` returns `description = null` (there is no description column) and `getImages` has its only real line commented out and returns an empty list, so the detail page never has a description or a picture. The `images/` directory with 35 JPEGs is unused.
- **C23. Admin panel is non-functional.** `AdminPanel.addItems` wraps the path in literal quote characters (`"\"" + path + "\""`) so the file is never found. `DatabaseManager.add_item` uses `executeQuery` for an `INSERT`, which Connector/J rejects. `getReport` reads `oi.quantity` but the column is `sum(oi.quantity)`, the resulting null causes an NPE, and `catch (Exception e){}` swallows it, so "Import Report" silently writes nothing. The "Number of Users" / "Number of Requests" labels are static text. The window title is "Hello World".
- **C24. `String` identity comparison.** `pass == ""` in `checkemail` and `validate` compares references. It happens to work because both sides are the interned literal, which is a trap for the next edit.
- **C25. Response schema drifts from what the client reads.** Order history labels the order id as `"Item ID"` and omits the total; order details omit `State` and the total; item list responses are fine. The client dutifully reads the missing keys and shows zeros.
- **C26. Dead code and unused state.** `Server.OpenConnection` opens a second server socket on the same address and is never called. `DataManager.userID` and `password` are never read. `DataManager(String, String)` is never called. `DatabaseManager.path`, `path2`, and the `getImages` file path are unused. Imports of `javax.xml.crypto.Data`, `BufferedImage`, and all of JavaFX in `MarketPlaceServer` are unused.
- **C27. Logging.** Every request and full response body, including base64 images and credentials, is written to stdout with `System.out.println`. There is no log level and no way to turn it off.

---

## 6. Findings: client correctness

| # | Where | Problem |
|---|---|---|
| K1 | `datamanager.cpp:413-467` (`getCart`, `checkout`) | Builds `cartJsonObj` with `ID` and `Cart`, then serialises `cartJsonDoc` (the raw array read from the file) instead. The server receives a bare array and dies (C11). **Neither cart retrieval nor checkout can work from the client.** [verified against server] |
| K2 | `datamanager.cpp:357-378` (`addToCart`) vs `ClientHandler.java:100` | Cart items are written as `{"ID","Quantity"}`; the server's checkout reads `"Item ID"`. Cart retrieval (ID 22) expects an array of plain integers. Even with K1 fixed, both shapes are wrong. |
| K3 | `datamanager.cpp:268` vs `ClientHandler.java:163` | Client sends `"OrderID"`, server reads `"Order ID"`. NPE server-side. [verified] |
| K4 | `cart.cpp:23-39`, `account.cpp:130-136`, `account.cpp:169-178`, `cart.cpp:129-133` | Writes through `operator[]` into `QVector`s that were never sized (`dci`, `id`, `img`, `names`, `prices`, `qu`, `ids`, `states`, `amounts`, `itemid`, `itempic`, ..., `upd`). Any non-empty cart, order history, or order detail is an out-of-bounds write. In a release build the Qt assert is compiled out, so this is silent memory corruption rather than a clean crash. [by reading; a `QVector` cannot be indexed past `size()`] |
| K5 | `datamanager.cpp:471-479` (`server_response`) | Reads `socket->readAll()` on each `readyRead` and parses it as one complete JSON document. Responses with icons are 40-200 KB and arrive across several `readyRead` events, so the parser sees fragments and silently emits nothing. There is no buffering and no framing. This is the client side of C8. |
| K6 | `datamanager.h:80`, `datamanager.cpp:539` | `CheckoutItem.availableQuantity` is a `bool`; the server sends an integer. `QJsonValue::toBool()` on a number returns the default `false`, so every item looks unavailable. |
| K7 | `shop.cpp:49-54` | Search button stores the text and does nothing; the request lines are commented out. Category list is displayed but has no click handler. Search and category filtering are not implemented. |
| K8 | `shop.cpp:69-105`, `cart.cpp`, `account.cpp` | Result slots append to member vectors and add widgets to the grid on every signal, never clearing. Because every dialog stays connected to the shared `DataManager` for its lifetime, opening the shop twice, or having two dialogs alive, duplicates rows. |
| K9 | `datamanager.cpp:20-24` | `waitForConnected()` with no timeout handling in the constructor; if the server is down the UI freezes for the default 30 s, then every `write` silently fails. No connection error is ever surfaced to the user. Server address and port are compile-time macros. |
| K10 | `datamanager.cpp:145-179` (`getSignInCredentials`) | Assigns the password into `signInData.email` (copy-paste). `signInfile` is never given a filename, so "Remember me" writes to a `QFile` with an empty name and fails. The function is never called anyway. If it worked, it would store the credential on disk in cleartext. |
| K11 | `datamanager.cpp:226-236` | In `updateAccountDetails`, `priceJsonObject` is inserted into the parent before its fields are set, so an empty `Price` object is sent. Harmless because the server ignores it, but it shows the copy is by value and the author expected a reference. |
| K12 | `datamanager.cpp:623` | `item.ID = value("Name").toInt()` in order details, always 0. |
| K13 | Money display everywhere | `QString::number(pounds) + "." + QString::number(piasters)` prints 12.05 as `12.5`. |
| K14 | `mainwindow.cpp:50-58`, `login.cpp:42-51` | Every dialog `new`s child dialogs on each click and never deletes them; parent-child ownership keeps them alive until the parent closes. Combined with K8, memory and duplicate signal handlers grow for the session. |
| K15 | `main.cpp:9-12` | `QApplication application = QApplication(argc, argv);` and friends rely on C++17 guaranteed elision for non-copyable types. Works, but is not idiomatic and will confuse readers. |

---

## 7. Findings: data model, protocol, repository

### Data model
- **D1. Unit confusion in seed data.** Code treats `itemprice` and `wallet` as piasters (divides by 100). Seed rows have `Grey sweatpants = 80` and `Iphone 13 pro = 24000`, which read as pounds. Either the seed is wrong by 100x or the code is. The shipped data makes a phone cost 240 EGP and sweatpants 0.80 EGP.
- **D2. No `AUTO_INCREMENT`, no description column, no image path column, no created/updated timestamps, no `users.id`** (email is the PK and the FK target, so an email change cascades through orders).
- **D3. No integrity for `orders.state`** (free-text `varchar(45)`, see C21) and no `CHECK (wallet >= 0)` or `quantity >= 0`.
- **D4. Dumps are MySQL 8 specific** (`utf8mb4_0900_ai_ci`) and split per table with no top-level schema or seed script.

### Protocol
- **P1. No framing** (length prefix or delimiter). This single omission is behind C8, C9, K5, and the spontaneous failures seen during testing.
- **P2. No error envelope.** Failures are either a boolean `Result`, an empty object, or silence. The client cannot distinguish "wrong password" from "server crashed".
- **P3. Magic integer IDs** with the schema living only in two files that have already drifted apart (K2, K3, C25).
- **P4. Images inline in list responses** (C7).

### Repository hygiene
- **R1. 1,372 of 1,538 tracked files are build output or IDE state**: three Qt build directories with `.o`, `.exe`, 76 DLLs, and 1,007 clangd `.idx` cache files; `Marketplace-Server/out/` with `.class` files and a 53 MB fat jar; the full Windows JavaFX 11 SDK (56 MB `jfxwebkit.dll` alone). Repository is 428 MB for about 5,000 lines of source.
- **R2. `.gitignore` has one entry**, `Marketplace-Server/.idea/workspace.xml`, and that file is tracked anyway.
- **R3. Six `Marketplace-Client.pro.user*` files** carrying five different developers' absolute paths (`C:/Users/DELL/...`, `D:/Senior 1 Semester 2/...`, `F:/Som3a/...`). These are per-machine Qt Creator state and should never be committed.
- **R4. No build system for the server.** Only IntelliJ `.iml`/`.idea` files. JavaFX and JDBC dependencies are vendored jars; the IntelliJ artifact config extracts the entire Windows SDK zip into the jar. A 15-line Maven or Gradle file would replace all of it and work on every OS.
- **R5. README is one line** (the repository name). No description, no setup steps, no protocol reference, no schema creation script.
- **R6. No tests** of any kind, on either side.
- **R7. Commit history** contains messages such as `zx`, `ddf`, `1 hour remaining`, `Final`, `Final 2`, plus a `Revert` pair. The history is not useful for understanding what changed and why.
- **R8. Two `MANIFEST.MF` files** in different places, one of them under a Maven-style `src/main/resources` path that nothing uses.

### Things done well
- Clear client/server split with a single networking class on each side.
- Java records for all DTOs; the protocol's request/response pairs are enumerated in one header on the client.
- Consistent use of `PreparedStatement`.
- Qt signal/slot decoupling between `DataManager` and the dialogs is the right pattern, even though the slots themselves are buggy.
- The client compiles warning-free under `-Wall -Wextra` on Qt 6.4 / GCC 13 on Linux, which it was never built on before.

---

## 8. Recommendations, in order

Do these in order; each one unblocks testing of the next.

1. **Stop the bleeding in the repo.** Add a real `.gitignore` (build dirs, `out/`, `*.o`, `*.class`, `*.pro.user*`, `.idea/workspace.xml`, `.qtc_clangd`), `git rm --cached` the 1,372 artifacts, and rotate the database password. Consider rewriting history to drop the 400 MB of binaries; if the repo is shared, coordinate first.
2. **Give the server a build.** A Maven `pom.xml` with `gson`, `mysql-connector-j`, and `org.openjfx:javafx-controls` (with the platform classifier) removes `lib/`, `JavaFX/`, and the IntelliJ artifact config. Externalise DB URL, user, password, and the icons directory into config or environment variables.
3. **Frame the protocol.** Prefix every message with a 4-byte big-endian length on both sides. On the server, read until the full length is buffered before parsing. On the client, accumulate in a `QByteArray` in `server_response` and only parse complete frames. This alone fixes C8, C9, K5, and most of the "it works on my machine" behaviour.
4. **Make the handler robust.** Wrap the body of `ClientHandler.run`'s loop in a `catch (RuntimeException)` that sends an error response `{"ID": <req+1>, "Error": "..."}` and continues, handle `read() == -1` by closing the socket, size the response buffer from `getBytes(UTF_8)`, and validate required fields before use. Add an error envelope to the protocol and have the client show it.
5. **Fix checkout end to end.** Compare `pounds*100 + piasters` on both sides; debit the wallet; do stock check, stock decrement, wallet debit, order insert, and order-item inserts in one JDBC transaction on one connection with `SELECT ... FOR UPDATE`; rename the result fields to match their meaning; make `orderid` and `itemid` `AUTO_INCREMENT`.
6. **Fix the SQL that never ran.** `user_purchase` (`orderid`, and use `add` not `set`), `OrderDetails` (add `oi.itemid` to the select), `dateorder` (alias the sum), `add_item` (`executeUpdate`), `item_list` (move `add` inside the loop, close connections). Use try-with-resources in every `DatabaseManager` method and let exceptions propagate so callers can report failure.
7. **Fix authentication.** Hash server-side with bcrypt/Argon2 (or at minimum PBKDF2) over the plaintext the client sends over TLS; drop the client-side SHA3-to-`QString` step entirely. Reject any non-catalogue request when `email` is null. Re-seed the customer table with properly hashed passwords.
8. **Fix the client's data flow.** Serialise `cartJsonObj`, not `cartJsonDoc`; use the server's key names (`Item ID`, `Order ID`); `resize()` or `append()` instead of indexing empty `QVector`s; clear the grid and vectors before repopulating; make `availableQuantity` an `int`; wire up search and category selection.
9. **Replace the thread model.** Either use the async API properly (completion handlers, no `.get()`), or drop `AsynchronousServerSocketChannel` for a plain `ServerSocket` with a cached thread pool or virtual threads (JDK 21). Either is simpler than the current hybrid and removes the 8-connection ceiling. Add a JDBC connection pool (HikariCP) instead of one connection per query.
10. **Add tests and docs.** A handful of JUnit tests around `DataManager.checkout` with an in-memory or containerised MySQL would have caught C3, C4, and C5. A README with setup steps, the protocol table, and the schema script would have saved every reviewer an afternoon.

---

## Appendix A. How the findings were reproduced

```bash
# Server
apt-get install -y mariadb-server openjfx
mysqld_safe --user=mysql &
mysql -e "ALTER USER 'root'@'localhost' IDENTIFIED VIA mysql_native_password USING PASSWORD('64deadpool128')"
mysql -uroot -p64deadpool128 -e "CREATE DATABASE marketplace"
for f in customer items orders orderitem; do
  sed 's/utf8mb4_0900_ai_ci/utf8mb4_unicode_ci/' Marketplace-Server/database/marketplace_$f.sql \
    | mysql -uroot -p64deadpool128 marketplace
done
javac -d /tmp/classes -cp "Marketplace-Server/lib/*" Marketplace-Server/src/*.java
# must run from repo root because of the relative icons path
java --module-path /usr/share/openjfx/lib --add-modules javafx.controls \
     -cp "/tmp/classes:Marketplace-Server/lib/gson-2.9.0.jar:Marketplace-Server/lib/mysql-connector-java-8.0.29.jar" \
     MarketPlaceServer

# Client
apt-get install -y qt6-base-dev qt6-base-dev-tools qmake6 libgl1-mesa-dev
mkdir build && cd build && qmake6 ../Marketplace-Client/Marketplace-Client/Marketplace-Client.pro && make -j4
QT_QPA_PLATFORM=offscreen ./Marketplace-Client
```

Protocol probes were sent with a small Python `socket` client that mirrors what `datamanager.cpp` builds for each request ID. The server's own stdout (it prints every request, response, and stack trace) was used to attribute each hang to its exception.

## Appendix B. Probe results summary

| Probe | Response | Server-side |
|---|---|---|
| categories, no login | full list | ok |
| item list, 2 categories, no login | 2 of 6 items, 203 KB | ok (C6, C7) |
| account details, no login | empty object | ok (S2) |
| deposit, no login | `Result: true` | 0 rows updated (S2) |
| login `weza` / `muhammed` (plaintext seed) | `true` | ok |
| login wrong password | `false` | ok |
| order history, user with orders | hang | `Column 'ID' not found`, NPE (C1) |
| order history, user without orders | `[]` | ok |
| order details | hang | `Column 'oi.itemid' not found`, NPE (C2) |
| order details with client's `OrderID` key | hang | NPE (K3) |
| deposit 10 / 250 | wallet 12.50 | ok (S4) |
| deposit -1000 / 0 | wallet -987.50 | ok (S4) |
| checkout 240.00 phone with 100.50 | order placed, stock -1, wallet unchanged | (C3) |
| checkout 0.15 cream with 100.00 | refused, "not enough funds" | (C4) |
| checkout 5 of an item with stock 2 | refused | ok, but flags inverted (C5) |
| register duplicate email | `false` | ok |
| register new email | `true` | ok |
| register 100-char name | `true` | `MysqlDataTruncation`, no row (C16) |
| register Arabic name then account details | hang | `BufferOverflowException` (C10) |
| two requests in one segment | hang | `MalformedJsonException` (C8) |
| 3,739-byte request | hang | `Unterminated string at column 2049` (C9) |
| bare array (real client checkout bytes) | hang | `Not a JSON Object` (C11, K1) |
| `{"ID":2}` | hang | NPE (C12) |
| `hello server` | hang | `MalformedJsonException` (C13) |
| `{"ID":999}` | `{}` | (C14) |
| 9th concurrent connection | hang until one closes | (C17) |
| after 3 item-list calls | 7 idle DB connections | (C18) |
| client disconnect | n/a | `NegativeArraySizeException: -1` per connection (C15) |
