import java.awt.image.BufferedImage;

public class DataManager {

    private int userID;

    public record RegistrationData(
            String Name,
            String email,
            String password,
            String address,
            double phone
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

    //public record MoneyAmount(
           // int pounds,
           // int piasters
    //) { }
    public record AccountDetails(
            String Name,
            String email,
            String address,
            double phone,
            int creditcard,
            double money
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
            double totalAmount
    ) { }

    public record DetailedOrderItem(
            String name,
            BufferedImage icon,
            double price,
            int quantity
    ) { }
    public record DetailedOrder(
            int ID,
            OrderState state,
            double totalAmount,
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
            double price
    ) { }

    public record DetailedItem(
            String name,
            String description,
            BufferedImage[] images,
            double price
    ) { }

    public boolean register(RegistrationData data) {
        return false;
    }

    public boolean authenticate(UserCredentials data) {
        return false;
    }

    public CheckoutResult checkout(CartItem data[]) {
        return null;
    }

    public AccountDetails getAccountDetails() {
        return null;
    }

    public void UpdateAccountDetails(AccountDetails data) {

    }

    public OrderSummary[] getOrderHistory() {
        return null;
    }

    public DetailedOrder getOrderDetails(int ID) {
        return null;
    }

    //function getWallet takes the email of the user and return double which is the total amount of money that customer have
    public boolean walletDeposit(double amount) {
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
