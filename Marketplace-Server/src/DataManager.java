import javax.xml.crypto.Data;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

public class DataManager {

    private int userID;
    private String email;
    private String password;
    private static Object mutex = new Object();


    public record RegistrationData(
            String firstName,
            String email,
            String password,
            String address,
            String phone
    ) {
    }

    public record UserCredentials(
            String email,
            String password
    ) {
    }

    public record CartItem(
            int ID,
            int quantity
    ) {
    }

    public record CheckoutItem(
            int ID,
            int availableQuantity
    ) {
    }

    public record CheckoutResult(
            boolean unavailableItem,
            boolean notEnoughFunds,
            ArrayList<CheckoutItem> itemAvailability
    ) {
    }

    public record MoneyAmount(
            int pounds,
            int piasters
    ) {
    }

    public record AccountDetails(
            String firstName,
            String email,
            String address,
            String phone,
            MoneyAmount amount
    ) {
    }

    public enum OrderState {
        ACCEPTED,
        SHIPPING,
        SHIPPED,
        REJECTED
    }

    public record OrderSummary(
            int ID,
            OrderState state,
            MoneyAmount totalAmount
    ) {
    }

    public record DetailedOrderItem(
            String name,
            String icon,
            MoneyAmount price,
            int quantity
    ) {
    }

    public record DetailedOrder(
            int ID,
            OrderState state,
            MoneyAmount totalAmount,
            ArrayList<DetailedOrderItem> items
    ) {
    }

    public record SearchQuery(
            String name,
            ArrayList<String> categories,
            int maxResults
    ) {
    }

    public record Item(
            int ID,
            String name,
            String icon,
            MoneyAmount price
    ) {
    }

    public record DetailedItem(
            String name,
            String description,
            ArrayList <String> images,
            MoneyAmount price
    ) {
    }


    //Constructor of class data manager
    public DataManager() {
        this.userID = 0;
        this.email = null;
        this.password = null;

    }

    public DataManager(String userEmail, String password) {
        this.email = userEmail;
        this.password = password;
    }


    //Done ,, needs testing
    public boolean register(RegistrationData data) {

        if (!DatabaseManager.checkemail(data.email())) {
            DatabaseManager.addRegister(data);

            this.email = data.email();
            return true;
        }
        return false;
    }


    // Done , needs testing
    public boolean authenticate(UserCredentials data) {

        if (DatabaseManager.validate(data)) {
            this.email = data.email();
            return true;
        }
        return false;
    }


    // Done , needs testing

    public CheckoutResult checkout(ArrayList<CartItem> data) {
        synchronized (mutex) {
            CheckoutResult output = null;
            ArrayList<CheckoutItem> out = new ArrayList<CheckoutItem>();
            boolean flag1 = false;
            boolean flag2 = false;
            MoneyAmount wallet = DatabaseManager.getWallet(this.email);
            MoneyAmount price = null;

            int pia = 0;
            int pou = 0;
            for (int j = 0; j < data.size(); j++) {
                int quan = DatabaseManager.getQuantity(data.get(j).ID());
                out.add(new CheckoutItem(data.get(j).ID(), quan));
            }
            for (int j = 0; j < out.size(); j++) {
                if (out.get(j).availableQuantity() >= data.get(j).quantity()) {

                    flag1 = true;
                } else {
                    flag1 = false;
                    break;
                }
            }
            for (int j = 0; j < data.size(); j++) {

                price = DatabaseManager.getPrice(data.get(j));
                pou += price.pounds();
                pia += price.piasters();
            }

            if ((pou / 100) + pia > (wallet.pounds() / 100) + wallet.piasters()) {
                flag2 = false;
            } else flag2 = true;
            if (flag1 && flag2) {
                for (int i = 0; i < data.size(); i++) {
                    int quan = DatabaseManager.getQuantity(data.get(i).ID());
                    int newQuantity = data.get(i).quantity();
                    int result = quan - newQuantity;
                    DatabaseManager.updateQuantity(data.get(i).ID(), result);

                }
                DatabaseManager.addOrder(data,this.email);

            }
            output = new CheckoutResult(flag1, flag2, out);
            return output;
        }
    }





    // Done .. needs testing
    public AccountDetails getAccountDetails()
    {

        AccountDetails userDetails = DatabaseManager.acc_details(this.email);

        return userDetails;
    }


    // done .. needs testing
    public boolean UpdateAccountDetails(AccountDetails data) {


        DatabaseManager.updateCustomer(data);
        //can't change the email and password
        return true;

    }


    // Done ,, needs testing
    public ArrayList<OrderSummary> getOrderHistory()
    {


        ArrayList<OrderSummary> orderHistory = DatabaseManager.user_purchase(this.email);

        return orderHistory;
    }


    // Done ,, needs testing
    public DetailedOrder getOrderDetails(int ID) {

        DetailedOrder orderDetails =DatabaseManager.OrderDetails(ID);

        return orderDetails;
    }

    //
    public boolean walletDeposit(MoneyAmount amount) {

        boolean transactionComplete = DatabaseManager.updateWallet(amount , this.email);

        return transactionComplete;
    }



      public ArrayList<Item> getItemList(SearchQuery query) {

        ArrayList<Item> item= DatabaseManager.item_list(query);


        return item;
    }



    public DetailedItem getItemData(int ID) {

        DetailedItem item_data = DatabaseManager.item_details(ID);

        return item_data;
    }

    public ArrayList<String> getCategories() {

        ArrayList<String> categories = DatabaseManager.getCategory();


        return categories;
    }

    public ArrayList<Item> getItemByID(ArrayList<Integer> itemIDs) {
        return null;
    }

}
