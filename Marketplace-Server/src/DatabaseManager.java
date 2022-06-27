import java.awt.image.BufferedImage;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class DatabaseManager {
    //to be modified
    static final String DB_URL = "jdbc:mysql://localhost:3306/marketplace";
    static final String USER = "root";
    static final String PASS = "1412001BAmr";

    private static String ImagesDirectory;

    public static BufferedImage[] getImages(int ID) {
        return null;
    }

    public static void start_connection() throws Exception {
        Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
        Statement stmt = connection.createStatement();
    }

    
}
