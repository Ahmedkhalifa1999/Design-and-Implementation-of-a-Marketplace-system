import javafx.application.Application;
import javafx.geometry.*;
import javafx.scene.*;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.scene.text.*;
import javafx.stage.Stage;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.text.ParseException;
import java.util.ArrayList;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import com.opencsv.CSVReader;

public class MarketplaceServer extends Application  {


    @Override
    public void start(Stage primaryStage) throws IOException {
        primaryStage.setTitle("Hello World");
        Group root = new Group();
        Scene scene = new Scene(root, 400, 400);
        // 1- "import report" button definition and handling the click
        Button btn = new Button();
        btn.setText("Import Report");
        Button btn2 = new Button();
        btn2.setText("Add Items");


        // 2- number of threads and requests text

        //int n = get number of threads
        //String t1 = String.valueOf(n); + "Number of Users:"
        //int m = get number of active threads
        //String t2 = String.valueOf(m); + "Number of Requests processing:"

        Text text1 = new Text(35 , 320, "Number of Users:");
        Text text2 = new Text(35 , 350, "Number of Requests processing:");
        root.getChildren().add(text1);
        root.getChildren().add(text2);

        Text text3 = new Text(100 , 250, "Invalid Date");


        // 3- text fields to enter date
        TextField startDate = new TextField();
        TextField endDate = new TextField();
        VBox layout = new VBox(10);

        Text sd = new Text ("Enter Start Date:");
        Text ed = new Text ("Enter End Date:");
        layout.setPadding(new Insets(35,45,45,35));
        TextField CSVPath = new TextField();
        Text path = new Text ("Enter CSV file path to add items:");
        layout.getChildren().addAll(path, CSVPath ,btn2 ,sd , startDate, ed, endDate , btn);
        root.getChildren().add(layout);


        btn.setOnAction(e-> getReport (startDate , endDate) );

        btn2.setOnAction(e-> addItems (CSVPath ) );


        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void addItems(TextField csvPath) {
        String path = "\"" + csvPath.getText()+ "\"";
        CSVReader reader = null;

        try
        {
            reader = new CSVReader(new FileReader(path));
            String [] nextLine;
            //read one line at a time

            while ((nextLine = reader.readNext()) != null)
            {
                String [] arr =  nextLine.split("[,]", 0);
                String name = arr[0];
                int price = Integer.parseInt(arr[1]);
                int quantity = Integer.parseInt(arr[2]);
                String category = arr[3];
                DatabaseManager.item item = new DatabaseManager.item (name, price, quantity, category);
                DatabaseManager.add_item(item);

            }


        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public void getReport ( TextField startDate , TextField endDate)
    {
        string start = startDate.getText();
        string end = endDate.getText();
        ArrayList<DatabaseManager.dateorderitem> arr =DatabaseManager.dateorder(start,end);
        File file = new File("report.csv");
        FileWriter fw = new FileWriter(file);
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write("Items:");
        bw.newLine();
        for(int i=0;i<arr.size();i++)
        {
            bw.write((arr.get(i)).itemname() +"," +(arr.get(i)).quantity());
            bw.newLine();
        }
        bw.close();
        fw.close();

    }

    public static void main(String[] args) {
        launch();
    }

}