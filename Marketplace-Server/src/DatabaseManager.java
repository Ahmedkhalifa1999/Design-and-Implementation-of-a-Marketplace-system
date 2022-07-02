import java.awt.image.BufferedImage;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.io.*;
import java.util.*;
import java.lang.String;
import java.util.ArrayList;


public class DatabaseManager {
    //to be modified
    static final String DB_URL = "jdbc:mysql://localhost:3306/marketplace";
    static final String USER = "root";
    static final String PASS = "64deadpool128";

    public record datedorderitem(
            String itemname,
            int quantity
    ) { }

    public record item(
            String itemname,
            int itemprice,
            int quantity,
            String Category
    ) { }

    //private static String ImagesDirectory;

    public static Connection start_connection() {
        try {
            Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
            return connection;
        }
        catch (Exception e)
        {
            e.printStackTrace();
            return null;
        }
    }

    public static void addRegister(DataManager.RegistrationData data)
    {
        try{
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("INSERT INTO customer (email, name, mobile, Address, wallet,password) VALUES (?,?,?,?,?,?)");
            statement.setString(1,data.email());
            statement.setString(2,data.firstName());
            statement.setString(3, data.phone());
            statement.setString(4, data.address());
            statement.setInt(5,0);
            statement.setString(6, data.password());
            statement.executeUpdate();
            connection.close();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }

    public static void updateCustomer (DataManager.AccountDetails data)
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("UPDATE customer SET name = ?, mobile = ?, Address = ?  WHERE email =?");
            //int pou = data.amount().pounds();
            //int pia= data.amount().piasters();
            //int temp = pou*100+pia;
            statement.setString(1, data.firstName());
            statement.setString(2, data.phone());
            statement.setString(3, data.address());
            //statement.setInt(4,temp);
            statement.setString(4,data.email());
            statement.executeUpdate();
            connection.close();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }

    public static boolean checkemail(String email)
    {
        try{
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT password FROM customer where email = ?");
            statement.setString(1,email);
            ResultSet resultSet = statement.executeQuery();
            String pass="";
            while(resultSet.next())
            {
                pass=resultSet.getString("password");
            }
            connection.close();
            if(pass=="")
            {
                return false;
            }
            return true;
        }
        catch (Exception e)
        {
            System.out.println(e);
            return false;
        }
    }

    public static ArrayList<DataManager.OrderSummary> user_purchase (String email)
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT orderid, state, totalprice FROM orders WHERE customeremail = ?");
            statement.setString(1, email);
            ResultSet rs = statement.executeQuery();
            int ID = 0, price = 0, arr_indx = 0;
            String state = "";
            ArrayList<DataManager.OrderSummary> res = new ArrayList<DataManager.OrderSummary>();
            while(rs.next()) {
                ID = rs.getInt("ID");
                price = rs.getInt("totalprice");
                state = rs.getString("state");
                int pou = (int)price / 100;
                int pia = (int)price % 100;
                DataManager.MoneyAmount tot_price = new DataManager.MoneyAmount(pou, pia);
                DataManager.OrderSummary temp = new DataManager.OrderSummary(ID, DataManager.OrderState.valueOf(state), tot_price);
                res.set(arr_indx++, temp);
            }
            connection.close();
            return res;
        }
        catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static ArrayList<DataManager.Item> item_list(DataManager.SearchQuery query) {
        try {
            ArrayList<DataManager.Item> res = new ArrayList<DataManager.Item>();
            int res_indx = 0;
            for (int i = 0; i < query.categories().size(); i++) {
                Connection connection = start_connection();
                PreparedStatement statement = connection.prepareStatement("SELECT itemid, itemname, itemprice FROM items WHERE itemname LIKE ? AND Category = ? LIMIT ?");
                statement.setString(1, "%" + query.name() + "%");
                statement.setString(2, query.categories().get(i));
                statement.setInt(3, query.maxResults());
                ResultSet rs = statement.executeQuery();
                String name = "", icon = "";
                int ID = 0, t_price = 0, pou = 0, pia = 0;
                DataManager.MoneyAmount price;
                while (rs.next()) {
                    ID = rs.getInt("itemid");
                    t_price = rs.getInt("itemprice");
                    name = rs.getString("itemname");
                    pou = (int)t_price/100;
                    pia = (int)t_price%100;
                    icon = getIcon(ID);
                }
                price = new DataManager.MoneyAmount(pou, pia);
                if (ID != 0) {
                    DataManager.Item ss = new DataManager.Item(ID, name, icon, price);
                    res.add(res_indx++, ss);
                }
            }
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static DataManager.DetailedOrder OrderDetails (int ID)

    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT o.orderid, o.state, o.totalprice, i.itemname, i.itemprice, oi.quantity FROM orders as o, orderitem as oi, items as i WHERE o.orderid = ? AND o.orderid = oi.orderid AND oi.itemid = i.itemid");
            statement.setInt(1, ID);
            ResultSet rs = statement.executeQuery();

            int o_price = 0, o_id = 0, o_pou = 0, o_pia = 0;
            ArrayList<Integer> i_price = new ArrayList<Integer>() , i_id = new ArrayList<Integer>(), i_quant = new ArrayList<Integer>();
            String state = "";
            ArrayList<String> i_name = new ArrayList<String>();
            ArrayList<DataManager.DetailedOrderItem> items = new ArrayList<DataManager.DetailedOrderItem>();
            while (rs.next()) {
                o_price = rs.getInt("o.totalprice");
                o_id = rs.getInt("o.orderid");
                state = rs.getString("o.state");
                i_id.add(rs.getInt("oi.itemid"));
                i_name.add(rs.getString("i.itemname"));
                i_price.add(rs.getInt("i.itemprice"));
                i_quant.add(rs.getInt("oi.quantity"));
            }
            o_pou = (int)o_price/100;
            o_pia = (int)o_price%100;

            for (int i = 0; i < i_id.size(); i++) {
                String i_image = getIcon(i_id.get(i));
                int i_pou = (int)(i_price.get(i).intValue())/100;
                int i_pia = (int)(i_price.get(i).intValue())%100;
                DataManager.MoneyAmount temp = new DataManager.MoneyAmount(i_pou, i_pia);
                DataManager.DetailedOrderItem di = new DataManager.DetailedOrderItem((String) i_name.get(i), i_image, temp, i_quant.get(i).intValue());
                items.add(i, di);
            }


            DataManager.MoneyAmount totalAmount = new DataManager.MoneyAmount(o_pou, o_pia);
            DataManager.DetailedOrder res = new DataManager.DetailedOrder(o_id, DataManager.OrderState.valueOf(state), totalAmount, items);
            connection.close();
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static ArrayList<datedorderitem> dateorder (String from ,String to)
    {
        try{
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("Select i.itemname , sum(oi.quantity) from orders as o , items as i , orderitem as oi where o.orderid=oi.orderid and i.itemid = oi.itemid and (o.placedate between ? and ?) group by i.itemname");
            statement.setString(1,from);
            statement.setString(2,to);
            ResultSet resultSet = statement.executeQuery();
            String name="";
            int q=0;
            ArrayList<datedorderitem> arr = new ArrayList<datedorderitem>();
            while (resultSet.next())
            {
                name = resultSet.getString("i.itemname");
                q=resultSet.getInt("oi.quantity");
                datedorderitem d = new datedorderitem(name,q);
                arr.add(d);
            }
            connection.close();
            return arr;

        }
        catch (Exception e)
        {
            System.out.println(e);
            return null;
        }
    }

    public static ArrayList<DataManager.Item> getItemByID_db (ArrayList<Integer> ids)
    {
        try {
            Connection connection = start_connection();
            ArrayList<DataManager.Item> res = new ArrayList<DataManager.Item>();
            for (int i = 0; i < ids.size(); i++) {
                PreparedStatement statement = connection.prepareStatement("SELECT itemid, itemname, itemprice FROM items WHERE itemid = ?");
                statement.setInt(1, ids.get(i));
                ResultSet rs = statement.executeQuery();
                String i_name = "";
                int i_id = 0, i_price = 0;
                int pou = 0, pia = 0;
                while (rs.next()) {
                    i_id = rs.getInt("itemid");
                    i_price = rs.getInt("itemprice");
                    pou = (int)i_price/100;
                    pia = (int)i_price%100;
                    i_name = rs.getString("itemname");
                }
                DataManager.MoneyAmount price = new DataManager.MoneyAmount(pou, pia);
                String icon = getIcon(ids.get(i));
                DataManager.Item temp = new DataManager.Item(i_id, i_name, icon, price);
                res.add(temp);
            }
            connection.close();
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static DataManager.AccountDetails acc_details (String email)
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM customer WHERE email = ?");
            statement.setString(1, email);
            ResultSet rs = statement.executeQuery();
            String temp_email = "";
            String firstName = "";
            String mobile = "";
            String Address = "";
            int pou = 0;
            int pia = 0;
            while(rs.next()) {
                   temp_email = rs.getString("email");
                   firstName = rs.getString("name");
                   mobile = rs.getString("mobile");
                   Address = rs.getString("Address");
                   int temp = rs.getInt("wallet");
                   pou = (int)temp / 100;
                   pia = (int)temp % 100;
            }

            DataManager.MoneyAmount money = new DataManager.MoneyAmount(pou, pia);
            DataManager.AccountDetails res = new DataManager.AccountDetails(firstName, email, Address, mobile, money);
            connection.close();
            return res;
        }
        catch (Exception e)
        {
            e.printStackTrace();
            return null;
        }
    }

    public static Boolean validate(DataManager.UserCredentials data)
    {
        try{
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT password FROM customer where email = ? and password = ?");
            statement.setString(1, data.email());
            statement.setString(2, data.password());
            ResultSet resultSet = statement.executeQuery();
            String pass="";
            while(resultSet.next())
            {
                pass=resultSet.getString("password");
            }
            connection.close();
            if(pass=="")
            {
                return false;
            }
            return true;
        }
        catch (Exception e)
        {
            System.out.println(e);
            return false;
        }
    }

    public static void add_item (item item)
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("select max(itemid) from items");
            ResultSet rs = statement.executeQuery();
            int no = 0;
            while (rs.next()) {
                no = rs.getInt("max(itemid)");
            }
            statement = connection.prepareStatement("INSERT INTO items VALUES (?, ?, ?, ?, ?)");
            statement.setInt(1, ++no);
            statement.setString(2, item.itemname());
            statement.setInt(3, item.itemprice());
            statement.setInt(4, item.quantity());
            statement.setString(5, item.Category());
            rs = statement.executeQuery();
            connection.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }


    public static DataManager.DetailedItem item_details(int ID)
    {

        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT itemname, itemprice FROM items WHERE itemid = ?");
            statement.setInt(1,ID);
            ResultSet rs = statement.executeQuery();
            ArrayList<String> images = getImages(ID); // arr of paths
            String name = "";
            int price = 0;
            while (rs.next()) {
                name = rs.getString("itemname");
                price = rs.getInt("itemprice");
            }
            int pou = (int)price/100;
            int pia = (int)price%100;
            DataManager.MoneyAmount f_price = new DataManager.MoneyAmount(pou, pia);
            DataManager.DetailedItem res = new DataManager.DetailedItem(name, null, images, f_price);
            connection.close();
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void addOrder (ArrayList<DataManager.CartItem> data, String email)
    {
        try
        {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT max(orderid) FROM marketplace.orders");
            ResultSet resultSet = statement.executeQuery();
            int id=0;
            while (resultSet.next())
            {
                id = resultSet.getInt("max(orderid)");
            }
            id++;
            statement = connection.prepareStatement("SELECT address from customer where email=?");
            statement.setString(1,email);
            resultSet=statement.executeQuery();
            String address="";
            while(resultSet.next())
            {
                address=resultSet.getString("address");
            }
            DataManager.MoneyAmount money;
            int pia=0;
            int pou=0;
            for (int i = 0;i<data.size();i++)
            {
                money = getPrice(data.get(i));
                pou += money.pounds();
                pia+= money.piasters();;
            }
            long temp = pou*100+pia;
            statement = connection.prepareStatement("INSERT INTO orders (orderid, placedate, arrivaldate,totalprice, customeremail , address, state) VALUES (?, ?, null,?,?,?,?)");
            statement.setInt(1,id);
            statement.setString(2, String.valueOf(java.time.LocalDate.now()));
            statement.setLong(3,temp);
            statement.setString(4,email);
            statement.setString(5,address);
            statement.setString(6,"ACCEPTED");
            statement.executeUpdate();

            statement = connection.prepareStatement("INSERT INTO orderitem (orderid, itemid,quantity) VALUES (?,?,?)");
            for (int i = 0;i< data.size();i++)
            {
                statement.setInt(1,id);
                statement.setInt(2,data.get(i).ID());
                statement.setInt(3,data.get(i).quantity());
                statement.executeUpdate();
            }
            connection.close();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }

    public static void updateQuantity (int ID,int quantity)
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("UPDATE items SET quantity = ? WHERE itemid = ?");
            statement.setInt(1,quantity);
            statement.setInt(2,ID);
            statement.executeUpdate();
            connection.close();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }

    public static int getQuantity(int ID)
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT quantity FROM items where itemid = ?");
            statement.setInt(1,ID);
            ResultSet resultSet = statement.executeQuery();
            int quantity=0;
            while (resultSet.next()) {
                quantity = resultSet.getInt("quantity");
            }
            connection.close();
            return quantity;
        }
        catch (Exception e)
        {
            System.out.println(e);
            return 0;
        }
    }

    public static DataManager.MoneyAmount getWallet(String email)
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT wallet from customer where email=?");
            statement.setString(1,email);
            ResultSet resultSet = statement.executeQuery();
            int pou=0;
            int pia=0;
            while (resultSet.next()) {
                pou = (int)(resultSet.getInt("wallet")/100);
                pia = (int)(resultSet.getInt("wallet")%100);
            }
            DataManager.MoneyAmount wallet = new DataManager.MoneyAmount(pou,pia);
            connection.close();
            return wallet;
        }
        catch (Exception e)
        {
            System.out.println(e);
            return null;
        }
    }

    public static boolean updateWallet (DataManager.MoneyAmount money, String email)
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("UPDATE customer SET wallet = wallet + ? WHERE email = ?");
            int temp = (int)money.pounds()*100 + (int)money.piasters();
            statement.setLong(1,temp);
            statement.setString(2,email);
            statement.executeUpdate();
            connection.close();
            return true;
        }
        catch (Exception e)
        {
            System.out.println(e);
            return false;
        }
    }
    public static DataManager.MoneyAmount getPrice(DataManager.CartItem item)
    {
        try{
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT itemprice FROM items where itemid = ?");
            statement.setInt(1,item.ID());
            long money=0;
            int quantity = item.quantity();
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next())
            {
                money = resultSet.getLong("itemprice");
            }
            long temp = quantity*money;
            int pia = (int)temp%100;
            int pou = (int)temp/100;

            DataManager.MoneyAmount m = new DataManager.MoneyAmount(pou,pia);
            connection.close();
            return m;

        }
        catch (Exception e)
        {
            System.out.println(e);
            return null;
        }
    }

    public static ArrayList <String> getCategory ()
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT distinct category FROM items");
            ResultSet resultSet = statement.executeQuery();
            ArrayList <String> arr=new ArrayList<String>();
            while (resultSet.next()) {
                arr.add(resultSet.getString("category"));
            }
            connection.close();
            return arr;
        }
        catch (Exception e)
        {
            System.out.println(e);
            return null;
        }
    }

    public static String findFilestr(String name,File file)
    {
        File[] list = file.listFiles();
        String out="";
        if (list != null)
            for (File fil : list) {
                boolean flag = true;
                String s = fil.getName();
                for (int i = 0; i < name.length(); i++) {
                    if (name.charAt(i) != s.charAt(i))
                        flag = false;
                }
                if (flag) {
                    out=fil.getPath();
                }

            }
        return out;
    }

    public static ArrayList<String> findFilearr(String name,File file) {
        File[] list = file.listFiles();
        ArrayList<String> arr = new ArrayList<String>();
        if (list != null)
            for (File fil : list) {
                boolean flag = true;
                String s = fil.getName();
                for (int i = 0; i < name.length(); i++) {
                    if (name.charAt(i) != s.charAt(i))
                        flag = false;
                }
                if (flag) {
                    arr.add(fil.getPath());
                }

            }
        return arr;
    }
    public static ArrayList<String> getImages(int ID) {
        //convert to string
        String s = String.valueOf(ID);
        File file = new File("Marketplace-Server/database/images");
        ArrayList<String> arr = new ArrayList<String>();
        //arr -> arraylist of paths of matched images
        arr = findFilearr(s, file);
        return arr;


    }

    public String getIcon(int ID) {
        //convert to string
        String s = String.valueOf(ID);
        File file = new File("C:\\Users\\HP\\Documents\\GitHub\\Design-and-Implementation-of-a-Marketplace-system\\Marketplace-Server\\database\\icons");
        //s+=".jpg";
        ArrayList<String> arr = new ArrayList<String>();
        arr=     findFilearr(s, file);
        return arr.get(0);
    }
}
