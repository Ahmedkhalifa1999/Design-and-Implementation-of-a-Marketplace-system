import javax.xml.crypto.Data;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

public class DataManager {

    private int userID;
    private String email;
    private String password;
    private Object mutex= new Object();



    public record RegistrationData(
            String firstName,
            String email,
            String password,
            String address,
            String phone
    ) { }

    public record UserCredentials(
            String email,
            String password
    ) { }

    public record CartItem(
            int ID,
            int quantity
    ) { }

    public record CheckoutItem(
            int ID,
            int availableQuantity
    ) { }
    public record CheckoutResult(
            boolean unavailableItem,
            boolean notEnoughFunds,
            CheckoutItem[] itemAvailability
    ) { }

    public record MoneyAmount(
            int pounds,
            int piasters
    ) { }
    public record AccountDetails(
            String firstName,
            String email,
            String address,
            String phone,
            MoneyAmount amount
    ) { }

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
    ) { }

    public record DetailedOrderItem(
            String name,
            String icon,
            MoneyAmount price,
            int quantity
    ) { }
    public record DetailedOrder(
            int ID,
            OrderState state,
            MoneyAmount totalAmount,
            ArrayList<DetailedOrderItem> items
    ) { }

    public record SearchQuery(
            String name,
            ArrayList<String> categories,
            int maxResults
    )
    { }

    public record Item(
            int ID,
            String name,
            String icon,
            MoneyAmount price
    ) { }

    public record DetailedItem(
            String name,
            String description,
            ArrayList<String> images,
            MoneyAmount price
    ) { }


    //Constructor of class data manager
    public DataManager()
    {
        this.userID = 0;
        this.email = null;
        this.password = null;

    }
    public DataManager(String userEmail , String password)
    {
        this.email = userEmail;
        this.password = password;
    }


    //Done ,, needs testing
    public boolean register(RegistrationData data) {

        if(!DatabaseManager.checkemail(data.email)){
            DatabaseManager.addRegister(data);
            DataManager user = new DataManager(data.email , data.password);
            return true;
        }
        return false;
    }


    // Done , needs testing
    public boolean authenticate(UserCredentials data) {

        if(DatabaseManager.validate(data))
        {
            DataManager user = new DataManager(data.email , data.password);
            return true;
        }
        return false;
    }


    // Done , needs testing

    public CheckoutResult checkout(CartItem data[]) {

        CheckoutResult output = null;
        CheckoutItem[] out = null;
        boolean flag1= false;
        boolean flag2= false;
        MoneyAmount wallet= DatabaseManager.getWallet(this.email);
        MoneyAmount price=null;

        int pia=0;
        int pou=0;
        for (int j = 0; j < data.length; j++) {
            int quan = DatabaseManager.getQuantity(data[j].ID());
            out[j] = new CheckoutItem(data[j].ID(), quan);
        }
        for (int j = 0; j < out.length; j++) {
            if (out[j].availableQuantity() >= data[j].quantity()) {

                flag1 = true;
            } else {
                flag1 = false;
                break;
            }
        }
        for (int j=0; j<data.length;j++) {

            price =DatabaseManager.getPrice(data[j]);
            pou+= price.pounds;
            pia+= price.piasters;
        }

        if ((pou/100)+pia>(wallet.pounds/100)+wallet.piasters) {
            flag2 = false;
        }
        else flag2= true;
        if (flag1 && flag2){
            for(int i=0; i<data.length;i++){
                int quan = DatabaseManager.getQuantity(data[i].ID());
                int newQuantity=data[i].quantity;
                int result = quan-newQuantity;
                synchronized (mutex) {
                    DatabaseManager.updateQuantity(data[i].ID, result);
                }
            }
        }
        return output= new CheckoutResult(flag1,flag2,out);

    }


    // Done .. needs testing
    public AccountDetails getAccountDetails()
    {

        AccountDetails userDetails = DatabaseManager.acc_details(this.email);

        return userDetails;
    }


    // done .. needs testing
    public void UpdateAccountDetails(AccountDetails data) {


        DatabaseManager.updateCustomer(data);
        //can't change the email and password

    }


    // Done ,, needs testing
    public ArrayList<OrderSummary> getOrderHistory()
    {


        ArrayList<OrderSummary> orderHistory = DatabaseManager.user_purchase(this.email);

        return orderHistory;
    }


    // Done ,, needs testing
    public DetailedOrder getOrderDetails(String email) {

        DetailedOrder orderDetails =DatabaseManager.OrderDetails(email);

        return orderDetails;
    }

    //
    public boolean walletDeposit(MoneyAmount amount) {

        boolean transactionComplete = DatabaseManager.updateWallet(amount , this.email);

        return transactionComplete;
    }



      public Item[] getItemList(SearchQuery query) {

        return null;
    }



    public DetailedItem getItemData(int ID) {

        DetailedItem item_data = DatabaseManager.item_details(ID);

        return item_data;
    }

    public ArrayList<String> getCategories() {

        ArrayList<String> categories = DatabaseManager.getCategory();


        return categories;
    }

}
