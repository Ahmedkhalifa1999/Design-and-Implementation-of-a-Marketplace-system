public class DataManager {

    private int userID;

    public record RegistrationData(
            String firstName,
            String lastName,
            String email,
            String password,
            String address,
            String phone
    ) { }

    public record UserCredentials(

    ) { }

    public record CartItem() {

    }

    public record CheckoutResult() {

    }

    public record AccountDetails() {

    }

    public record OrderSummary() {

    }

    public record DetailedOrder() {

    }

    public record MoneyAmount() {

    }

    public record SearchQuery() {

    }

    public record Item() {

    }

    public record DetailedItem() {

    }

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
