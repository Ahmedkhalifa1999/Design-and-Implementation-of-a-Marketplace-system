import java.awt.image.BufferedImage;

public class DatabaseManager {
    //to be modified
    static final String DB_URL = "jdbc:mysql://localhost:3306/world";
    static final String USER = "root";
    static final String PASS = "Memo485213697";

    private static String ImagesDirectory;

    public static BufferedImage[] getImages(int ID) {
        return null;
    }

    public static void start_connection() throws Exception {
        Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
        Statement stmt = connection.createStatement();
    }

    
}
