import java.awt.image.BufferedImage;
import java.util.ArrayList;

public class DataManager {

    private int userID;

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
