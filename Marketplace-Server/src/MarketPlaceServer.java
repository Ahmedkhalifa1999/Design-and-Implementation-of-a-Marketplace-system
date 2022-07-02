import javafx.application.Application;
import javafx.geometry.*;
import javafx.scene.*;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.scene.text.*;
import javafx.stage.Stage;

import java.io.*;
import java.util.ArrayList;

public class MarketPlaceServer {
    public static void main(String[] args) {
        Server marketplace = new Server();
        Thread serverThread = new Thread(marketplace);
        serverThread.start();
        AdminPanel panel = new AdminPanel();
        Thread guiThread = new Thread(panel);
        guiThread.start();
        try {
            serverThread.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

}