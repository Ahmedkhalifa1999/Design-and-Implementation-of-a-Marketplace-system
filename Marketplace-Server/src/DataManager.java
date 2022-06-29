import javax.xml.crypto.Data;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

public class DataManager {

    private int userID;
    private String email;
    private String password;



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
            DetailedOrderItem[] items
    ) { }

    public record SearchQuery(
            String name,
            String[] categories,
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

        
        return false;
    }


    // Done , needs testing
    public CheckoutResult checkout(CartItem data[])
    {

    }


    // Done .. needs testing
    public AccountDetails getAccountDetails()
    {

        AccountDetails userDetails = DatabaseManager.acc_details(this.email);

        //call the function to get name, email , address , phone , amount of money

        return userdetails;
    }


    // done .. needs testing
    public void UpdateAccountDetails(AccountDetails data) {


        updateCustomer(data);

        // update the data for this user in the database.

    }


    // Done ,, needs testing
    public ArrayList<OrderSummary> getOrderHistory()
    {

        return null;
    }


    // Done ,, needs testing
    public DetailedOrder getOrderDetails(int ID) {

        return null;
    }

    //
    public boolean walletDeposit(MoneyAmount amount) {

        boolean transactionComplete = DatabaseManager.updateWallet(amount , this.email);



        return transactionComplete;
    }

    /*
    public record SearchQuery(
            String name,
            String[] categories,
            int maxResults
    )
    { }

    public record Item(
            int ID,
            String name,
            String icon,
            MoneyAmount price
    ) { }
    */

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
