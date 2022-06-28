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

    public static void start_connection() {
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

    public double getWallet(String email)
    {
        try {
            Connection connection = start_connection();
            PreparedStatement statement = connection.prepareStatement("SELECT wallet from customer where email=?");
            statement.setString(1,email);
            ResultSet resultSet = statement.executeQuery();
            double wallet = 0;
            while (resultSet.next()) {
                wallet = resultSet.getInt("wallet");
            }
            return wallet;
        }
        catch (Exception e)
        {
            System.out.println(e);
            return 1;
        }
    }

    public static ArrayList<String> getImages(int ID) {
        //convert to string
        String s = String.valueOf(ID);
        File file = new File("Marketplace-Server/database/images");
        ArrayList<String> arr = new ArrayList<String>();
        //arr -> arraylist of paths of matched images
        arr = findFile(s, file);
        File[] list = file.listFiles();


    }

    public static String getIcon (int ID)
    {
        //convert to string
        String str= String.valurOf(ID);
        String out;
        File file = new File("Marketplace-Server/database/icons");
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



    public ArrayList<String> findFile(String name,File file) {
        File[] list = file.listFiles();
        ArrayList<String> arr = new ArrayList<String>();
        int str_indx = 0;
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
    //    public static void store_item_data()
}
