import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousSocketChannel;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Base64;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import com.google.gson.*;


/*
1- parsing json function and put the data in bufferReader
2-
*/
public class ClientHandler implements Runnable
{

    private static final Base64.Encoder ImageEncoder = Base64.getUrlEncoder();


    /*
    socket is used for starting the connection
    BufferReader contains the data from the client
    BufferWriter contains the data for the client
    */
    private AsynchronousSocketChannel socket;
    private DataManager dataManager;

    public ClientHandler(Future<AsynchronousSocketChannel> socket)
    {
        try {
            this.socket = socket.get();
            System.out.println("Connection Accepted");
            dataManager = new DataManager();
        }
        catch(Exception e){
            closeEverything(socket);
        }
    }
    public void closeEverything(Future<AsynchronousSocketChannel> socket)
    {

        if(socket != null){
            socket.cancel(true);
        }

    }

    @Override
    public void run() {
        // Continue to listen for messages while a connection with the client is still established.
        while (this.socket.isOpen()) {

            try {
                // Read what the client sent and then send it to every other client.
                ByteBuffer readBuffer = ByteBuffer.allocate(2048);
                Future<Integer> dataSize = socket.read(readBuffer);
                System.out.println("Waiting for data");
                int number = dataSize.get();
                System.out.println(number);
                byte[] dataBytes = new byte[number];
                readBuffer.flip();
                readBuffer.get(dataBytes);
                String request = new String(dataBytes, StandardCharsets.UTF_8);
                System.out.println(request);
                //Parse Request
                JsonObject requestObject = JsonParser.parseString(request).getAsJsonObject();
                JsonObject responseObject = new JsonObject();

                int ID = requestObject.get("ID").getAsInt();
                switch (ID) {
                    case 0 -> { //register
                        boolean registerResult = dataManager.register(new DataManager.RegistrationData(
                                requestObject.get("Name").getAsString(),
                                requestObject.get("Email").getAsString(),
                                requestObject.get("Password").getAsString(),
                                requestObject.get("Address").getAsString(),
                                requestObject.get("Phone").getAsString()
                        ));
                        responseObject.addProperty("ID", 1);
                        responseObject.addProperty("Result", registerResult);
                    }
                    case 2 -> { //authenticate
                        boolean authenticateResult = dataManager.authenticate(new DataManager.UserCredentials(
                                requestObject.get("Email").getAsString(),
                                requestObject.get("Password").getAsString()
                        ));
                        responseObject.addProperty("ID", 3);
                        responseObject.addProperty("Result", authenticateResult);
                    }
                    case 4 -> {
                        //checkout
                        JsonArray JSON_cart = requestObject.get("Cart").getAsJsonArray();
                        ArrayList<DataManager.CartItem> Data_cart = new ArrayList<>();
                        for (JsonElement JSON_item : JSON_cart) {
                            Data_cart.add(new DataManager.CartItem(
                                    JSON_item.getAsJsonObject().get("Item ID").getAsInt(),
                                    JSON_item.getAsJsonObject().get("Quantity").getAsInt()
                            ));
                        }
                        DataManager.CheckoutResult checkoutResult =
                                dataManager.checkout(Data_cart);
                        responseObject.addProperty("Unavailable", checkoutResult.unavailableItem());
                        responseObject.addProperty("Funds", checkoutResult.notEnoughFunds());
                        JsonArray JSON_availability = new JsonArray();
                        for (DataManager.CheckoutItem itemAvailability : checkoutResult.itemAvailability()) {
                            JsonObject JSON_itemAvailability = new JsonObject();
                            JSON_itemAvailability.addProperty("Item ID", itemAvailability.ID());
                            JSON_itemAvailability.addProperty("Quantity", itemAvailability.availableQuantity());
                            JSON_availability.add(JSON_itemAvailability);
                        }
                        responseObject.addProperty("ID", 5);
                        responseObject.add("Availability", JSON_availability);
                    }
                    case 6 -> {
                        //get account details
                        DataManager.AccountDetails accountDetails = dataManager.getAccountDetails();
                        responseObject.addProperty("First Name", accountDetails.firstName());
                        responseObject.addProperty("Last Name", accountDetails.firstName());
                        responseObject.addProperty("Email", accountDetails.email());
                        responseObject.addProperty("Address", accountDetails.address());
                        responseObject.addProperty("Phone", accountDetails.phone());
                        DataManager.MoneyAmount wallet_data = accountDetails.amount();
                        JsonObject wallet_JSON = new JsonObject();
                        wallet_JSON.addProperty("Pounds", wallet_data.pounds());
                        wallet_JSON.addProperty("Piasters", wallet_data.piasters());
                        responseObject.addProperty("ID", 7);
                        responseObject.add("Wallet", wallet_JSON);
                    }
                    case 8 -> {
                        //update account details
                        boolean updateResult = dataManager.UpdateAccountDetails(new DataManager.AccountDetails(
                                requestObject.get("Name").getAsString(),
                                requestObject.get("Email").getAsString(),
                                requestObject.get("Address").getAsString(),
                                requestObject.get("Phone").getAsString(),
                                null
                        ));
                        responseObject.addProperty("ID", 9);
                        responseObject.addProperty("Result", updateResult);
                    }
                    case 10 -> {
                        //get order history
                        JsonArray orderHistory_JSON = new JsonArray();
                        for (DataManager.OrderSummary order_data : dataManager.getOrderHistory()) {
                            JsonObject JSON_order = new JsonObject();
                            JSON_order.addProperty("Item ID", order_data.ID());
                            JSON_order.addProperty("Order State", order_data.state().ordinal());
                            JsonObject JSON_orderSummaryAmount = new JsonObject();
                            JSON_orderSummaryAmount.addProperty("Pounds", order_data.totalAmount().pounds());
                            JSON_orderSummaryAmount.addProperty("Piasters", order_data.totalAmount().piasters());
                            orderHistory_JSON.add(JSON_order);
                        }
                        responseObject.addProperty("ID", 11);
                        responseObject.add("Order History", orderHistory_JSON);
                    }
                    case 12 -> {
                        //get order details
                        DataManager.DetailedOrder detailedOrder =
                                dataManager.getOrderDetails(requestObject.get("Order ID").getAsInt());
                        responseObject.addProperty("ID", 13);
                        responseObject.add("Order ID", requestObject.get("Order ID"));
                        JsonArray orderItems_JSON = new JsonArray();
                        for (DataManager.DetailedOrderItem orderItem_data : detailedOrder.items()) {
                            JsonObject JSON_orderItem = new JsonObject();
                            JSON_orderItem.addProperty("Name", orderItem_data.name());
                            JSON_orderItem.addProperty("Icon",
                                    new String(ImageEncoder.encode(Files.readAllBytes(Path.of(orderItem_data.icon())))));
                            JsonObject JSON_detailedOrderItemAmount = new JsonObject();
                            JSON_detailedOrderItemAmount.addProperty("Pounds", orderItem_data.price().pounds());
                            JSON_detailedOrderItemAmount.addProperty("Piasters", orderItem_data.price().piasters());
                            JSON_orderItem.add("Price", JSON_detailedOrderItemAmount);
                            JSON_orderItem.addProperty("Quantity", orderItem_data.quantity());
                            orderItems_JSON.add(JSON_orderItem);
                        }
                        responseObject.add("Items", orderItems_JSON);
                        JsonObject JSON_detailedOrderAmount = new JsonObject();
                        JSON_detailedOrderAmount.addProperty("Pounds", detailedOrder.totalAmount().pounds());
                        JSON_detailedOrderAmount.addProperty("Piasters", detailedOrder.totalAmount().piasters());
                    }
                    case 14 -> {
                        //wallet deposit
                        boolean depositResult = dataManager.walletDeposit(new DataManager.MoneyAmount(
                                requestObject.get("Amount").getAsJsonObject().get("Pounds").getAsInt(),
                                requestObject.get("Amount").getAsJsonObject().get("Piasters").getAsInt()
                        ));
                        responseObject.addProperty("ID", 15);
                        responseObject.addProperty("Result", depositResult);
                    }
                    case 16 -> {
                        //get item list
                        String searchQueryName = requestObject.get("Name").getAsString();
                        ArrayList<String> searchQueryCategories = new ArrayList<>();
                        for (JsonElement JSON_category : requestObject.get("Categories").getAsJsonArray()) {
                            searchQueryCategories.add(JSON_category.getAsString());
                        }
                        int searchQueryMaxResults = requestObject.get("Max Results").getAsInt();
                        DataManager.SearchQuery searchQuery =
                                new DataManager.SearchQuery(searchQueryName, searchQueryCategories, searchQueryMaxResults);
                        ArrayList<DataManager.Item> searchResults = dataManager.getItemList(searchQuery);
                        JsonArray JSON_items = new JsonArray();
                        for (DataManager.Item result : searchResults) {
                            JsonObject JSON_item = new JsonObject();
                            JSON_item.addProperty("Item ID", result.ID());
                            JSON_item.addProperty("Name", result.name());
                            if (Files.exists(Path.of(result.icon())) && result.icon() != "")
                                JSON_item.addProperty("Icon",
                                        new String(ImageEncoder.encode(Files.readAllBytes(Path.of(result.icon())))));
                            else
                                JSON_item.addProperty("Icon", "");
                            JsonObject JSON_itemPrice = new JsonObject();
                            JSON_itemPrice.addProperty("Pounds", result.price().pounds());
                            JSON_itemPrice.addProperty("Piasters", result.price().piasters());
                            JSON_item.add("Price", JSON_itemPrice);
                            JSON_items.add(JSON_item);
                        }
                        responseObject.addProperty("ID", 17);
                        responseObject.add("Items", JSON_items);
                    }
                    case 18 -> {
                        //get item data
                        DataManager.DetailedItem detailedItem =
                                dataManager.getItemData(requestObject.get("Item ID").getAsInt());
                        responseObject.addProperty("ID", 19);
                        responseObject.addProperty("Name", detailedItem.name());
                        responseObject.addProperty("Description", detailedItem.description());
                        JsonArray itemImages_JSON = new JsonArray();
                        for (String itemImage : detailedItem.images()) {
                            if (Files.exists(Path.of(itemImage)) && itemImage != "")
                                itemImages_JSON.add(new String(ImageEncoder.encode(Files.readAllBytes(Path.of(itemImage)))));
                            else
                                itemImages_JSON.add("");
                        }
                        responseObject.add("Images", itemImages_JSON);
                        JsonObject detailedItemPrice = new JsonObject();
                        detailedItemPrice.addProperty("Pounds", detailedItem.price().pounds());
                        detailedItemPrice.addProperty("Piasters", detailedItem.price().piasters());
                        responseObject.add("Price", detailedItemPrice);
                    }
                    case 20 -> {
                        //get categories request
                        ArrayList<String> categories = dataManager.getCategories();
                        JsonArray JSON_categories = new JsonArray();
                        for (String category : categories) {
                            JSON_categories.add(category);
                        }
                        responseObject.addProperty("ID", 21);
                        responseObject.add("Categories", JSON_categories);
                    }
                }

                Gson JSONBuilder = new Gson();
                String response = JSONBuilder.toJson(responseObject);
                System.out.println(response);
                ByteBuffer writeBuffer = ByteBuffer.allocate(response.length());
                writeBuffer.put(response.getBytes());
                writeBuffer.flip();
                Future<Integer> writtenBytes = socket.write(writeBuffer);
                System.out.println(writtenBytes.get());

            } catch (InterruptedException | ExecutionException | IOException e) {
                // Close everything gracefully.
                if(socket != null){
                    try {
                        socket.close();
                    }
                    catch (IOException IOe) {
                        return;
                    }
                }
                break;
            }
        }
    }
}