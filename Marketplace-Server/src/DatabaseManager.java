import java.awt.image.BufferedImage;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.io.*;
import java.util.*;

public class DatabaseManager {
    //to be modified
    static final String DB_URL = "jdbc:mysql://localhost:3306/marketplace";
    static final String USER = "root";
    static final String PASS = "1412001BAmr";

    private static String ImagesDirectory;

    public static BufferedImage[] getImages(int ID) {
        //convert to string
        String s = String.valueOf(ID);

        File file = new File("Marketplace-Server/database/images");
        String[] arr = new String[10];
        //arr -> array of paths of matched images
        arr = findFile(s, file);

    }

    public static void start_connection() throws Exception {
        Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
        PreparedStatement pstmt = null;
    }

    public String[] findFile(String name,File file) {
        File[] list = file.listFiles();
        String[] arr = new String[10];
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
                    arr[str_indx++] = fil.getPath();
                }

            }
        return arr;
    }
    //    public static void store_item_data()
}
