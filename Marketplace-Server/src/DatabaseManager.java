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
    static final String PASS = "1412001BAmr";

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
    
    public void addRegister(DataManager.RegistrationData data)
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
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }

    public void updateCustomer (DataManager.AccountDetails data)
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("UPDATE customer SET name = ?, mobile = ?, Address = ?, wallet = ?  WHERE email =?");
            int pou = data.amount().pounds();
            int pia= data.amount().piasters();
            int temp = pou*100+pia;
            statement.setString(1, data.firstName());
            statement.setString(2, data.phone());
            statement.setString(3, data.address());
            statement.setInt(4,temp);
            statement.setString(5,data.email());
            statement.executeUpdate();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }

    public boolean checkemail(String email)
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

    public ArrayList<DataManager.OrderSummary> user_purchase (String email)
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT ID, state, totalprice FROM customer WHERE email = ?");
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
            return res;
        }
        catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }


    public DataManager.AccountDetails acc_details (String email)
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
            return res;
        }
        catch (Exception e)
        {
            e.printStackTrace();
            return null;
        }
    }

    public Boolean validate(DataManager.UserCredentials data)
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

    public void updateQuantity (int ID,int quantity)
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("UPDATE items SET quantity = ? WHERE itemid = ?");
            statement.setInt(1,quantity);
            statement.setInt(2,ID);
            statement.executeUpdate();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }

    public int getQuantity(int ID)
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
            return quantity;
        }
        catch (Exception e)
        {
            System.out.println(e);
            return 0;
        }
    }

    public DataManager.MoneyAmount getWallet(String email)
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
            return wallet;
        }
        catch (Exception e)
        {
            System.out.println(e);
            return null;
        }
    }

    public boolean updateWallet (DataManager.MoneyAmount money, String email)
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("UPDATE customer SET wallet = wallet + ? WHERE email = ?");
            int temp = (int)money.pounds()*100 + (int)money.piasters();
            statement.setLong(1,temp);
            statement.setString(2,email);
            statement.executeUpdate();
            return true;
        }
        catch (Exception e)
        {
            System.out.println(e);
            return false;
        }
    }
    public DataManager.MoneyAmount getPrice(DataManager.CartItem item)
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
            return m;

        }
        catch (Exception e)
        {
            System.out.println(e);
            return null;
        }
    }

    public ArrayList <String> getCategory ()
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT distinct category FROM items");
            ResultSet resultSet = statement.executeQuery();
            ArrayList <String> arr=new ArrayList<String>();
            while (resultSet.next()) {
                arr.add(resultSet.getString("category"));
            }
            return arr;
        }
        catch (Exception e)
        {
            System.out.println(e);
            return null;
        }
    }

    public String findFilestr(String name,File file)
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

    public ArrayList<String> findFilearr(String name,File file) {
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
    public ArrayList<String> getImages(int ID) {
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
        File file = new File("Marketplace-Server/database/icons");
        String str = findFilestr(s, file);
        return str;
    }
}
