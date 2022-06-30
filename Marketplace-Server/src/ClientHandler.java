import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousSocketChannel;
import java.nio.channels.ByteChannel;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import com.google.gson.*;


/*
1- parsing json function and put the data in bufferReader
2-
*/
public class ClientHandler implements Runnable
{


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
            dataManager = new DataManager();
        }
        catch(Exception e){
            closeEverything(socket);
        }
    }

    public void closeEverything(Future<AsynchronousSocketChannel> socket)
    {

        if(socket != null){
            boolean flag;
            flag = socket.cancel(true);
        }

    }

    @Override
    public void run() {
        // Continue to listen for messages while a connection with the client is still established.
        while (this.socket.isOpen()) {

            try {
                // Read what the client sent and then send it to every other client.
                ByteBuffer readBuffer = ByteBuffer.allocate(20480);
                Future<Integer> dataSize = socket.read(readBuffer);
                byte[] dataBytes = new byte[dataSize.get()];
                readBuffer.get(dataBytes);
                String request = new String(dataBytes, StandardCharsets.UTF_8);
                //Parse Request
                JsonObject requestObject = JsonParser.parseString(request).getAsJsonObject();
                JsonObject responseObject = new JsonObject();

                int ID = requestObject.get("ID").getAsInt();
                switch (ID) {
                    case 0: //register
                        boolean registerResult = dataManager.register(new DataManager.RegistrationData(
                                requestObject.get("Name").getAsString(),
                                requestObject.get("Email").getAsString(),
                                requestObject.get("Password").getAsString(),
                                requestObject.get("Address").getAsString(),
                                requestObject.get("Phone").getAsString()
                        ));
                        responseObject.addProperty("ID", 1);
                        responseObject.addProperty("Result", registerResult);
                        break;
                    case 2: //authenticate
                        boolean authenticateResult = dataManager.authenticate(new DataManager.UserCredentials(
                                requestObject.get("Email").getAsString(),
                                requestObject.get("Password").getAsString()
                        ));
                        responseObject.addProperty("ID", 1);
                        responseObject.addProperty("Result", authenticateResult);
                        break;
                    case 4:
                        //checkout
                        JsonArray JSON_cart = requestObject.get("Cart").getAsJsonArray();
                        ArrayList<DataManager.CartItem> Data_cart = new ArrayList<DataManager.CartItem>();
                        for (JsonElement JSON_item: JSON_cart) {
                            Data_cart.add(new DataManager.CartItem(
                                    JSON_item.getAsJsonObject().get("Item ID").getAsInt(),
                                    JSON_item.getAsJsonObject().get("Quantity").getAsInt()
                            ));
                        }
                        DataManager.CheckoutResult checkoutResult =
                                dataManager.checkout((DataManager.CartItem[]) Data_cart.toArray());
                        responseObject.addProperty("Unavailable", checkoutResult.unavailableItem());
                        responseObject.addProperty("Funds", checkoutResult.notEnoughFunds());
                        JsonArray JSON_availability = new JsonArray();
                        for (DataManager.CheckoutItem itemAvailability: checkoutResult.itemAvailability()) {
                            JsonObject JSON_itemAvailability = new JsonObject();
                            JSON_itemAvailability.addProperty("Item ID", itemAvailability.ID());
                            JSON_itemAvailability.addProperty("Quantity", itemAvailability.availableQuantity());
                            JSON_availability.add(JSON_itemAvailability);
                        }
                        responseObject.add("Availability", JSON_availability);
                        break;
                    case 6:
                        //get account details

                        break;
                    case 8:
                        //update account details
                        break;
                    case 10:
                        //get order history
                        break;
                    case 12:
                        //get order details
                        break;
                    case 14:
                        //wallet deposit
                        break;
                    case 16:
                        //get item list
                        break;
                    case 18:
                        //get item data
                        break;
                    case 20:
                        //get categories request
                        break;
                }

                Gson JSONBuilder = new Gson();
                String response = JSONBuilder.toJson(responseObject);
                ByteBuffer writeBuffer = ByteBuffer.allocate(response.length());
                writeBuffer.put(response.getBytes());
                Future<Integer> writtenBytes = socket.write(writeBuffer);
                writtenBytes.get();

            } catch (InterruptedException | ExecutionException e) {
                // Close everything gracefully.
                if(socket != null){
                    try {
                        socket.close();
                    }
                    catch (IOException IOe) {
                        return;
                    }
                };
                break;
            }
        }
    }
}