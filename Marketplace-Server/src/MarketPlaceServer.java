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


import java.io.IOException;

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

        String sDate = startDate.getText();
        String eDate = endDate.getText();
        btn.setOnAction(e-> {
            try {
                ParseDate(startDate , endDate);
            } catch (ParseException ex) {
                throw new RuntimeException(ex);
            }
        });


        btn2.setOnAction(e-> addItems (CSVPath ) );


        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void addItems(TextField csvPath) {
        String path = csvPath.getText();
        System.out.println(path);
    }

    public void ParseDate (TextField startDate , TextField endDate) throws ParseException {
        try {
            String sd = startDate.getText();
            String ed = endDate.getText();
            Date sdate = new SimpleDateFormat("dd/MM/yyyy").parse(sd);
            Date edate = new SimpleDateFormat("dd/MM/yyyy").parse(ed);

        }
        catch (ParseException e)
        {
            System.out.println("Error!");
        }

    }


    public static void main(String[] args) {
        launch();
    }
}