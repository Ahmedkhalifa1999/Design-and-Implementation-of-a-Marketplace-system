import java.awt.image.BufferedImage;

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
            BufferedImage icon,
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
            BufferedImage icon,
            MoneyAmount price
    ) { }

    public record DetailedItem(
            String name,
            String description,
            BufferedImage[] images,
            MoneyAmount price
    ) { }

    public boolean register(RegistrationData data) {



        if(!DatabaseManager.checkemail(data)){
            DatabaseManager.addRegister(data);
            return true;
        }

        return false;
    }

    public boolean authenticate(UserCredentials data) {

        if(DatabaseManager.validate(data))
        {
            return true;
        }
        return false;
    }

/*
  public record CheckoutItem(
            int ID,
            int availableQuantity
    ) { }
    public record CheckoutResult(
            boolean unavailableItem,
            boolean notEnoughFunds,
            CheckoutItem[] itemAvailability
    ) { }

 */
    public CheckoutResult checkout(CartItem data[]) {

        CheckoutResult output;
        CheckoutItem[] out= null;
        boolean flag;

    for(int j=0; j< data.length; j++) {
        int quan = DatabaseManager.getQuantity(data[i].ID());
        out[j] = new CheckoutItem(data[j].ID(), quan);
    }
    for (int j=0; j<out.length; j++){
        if(out[j].availableQuantity()< data[j].quantity()){
            flag= true;

        }
        else {
            flag= false;
            break;

        }
    }

    for (int j=0; j<out.length; j++){
        if
    }



        return null;
    }


    public AccountDetails getAccountDetails() {

        //call the function to get name, email , address , phone , amount of money

        AccountDetails userdetails;



        return userdetails;
    }

    public void UpdateAccountDetails(AccountDetails data) {

        // update the data for this user in the database.

    }


    public OrderSummary getOrderHistory() {

        // call the function and get the orderid , state of the order , the total price of the order
        OrderSummary orderdata;

        return orderdata;
    }

    public DetailedOrder getOrderDetails(int ID) {



        return null;
    }

    public boolean walletDeposit(MoneyAmount amount) {
        return true;
    }

    public Item[] getItemList(SearchQuery query) {
        return null;
    }

    public DetailedItem getItemData(int ID) {
        return null;
    }

    public String[] getCategories() {
        return null;
    }

}
