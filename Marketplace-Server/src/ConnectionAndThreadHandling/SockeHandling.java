package ConnectionAndThreadHandling;

import java.net.*;
import java.io.*;


public class SockeHandling {
    /*
    1- ServerSocket is the port number where the connection will be established
    2- The Server starts the connection
    3- by taking the data to the client handler to handle and parsing the request given by the user
    4- Every request from the user will make a thread
    5- After finishing the connection go to closeServerSocket.
    */
    private final ServerSocket serverSocket;

    public SockeHandling(ServerSocket serverSocket)
    {
        this.serverSocket = serverSocket;
    }


    public void StartServer()
    {
        try{
            while(!serverSocket.isClosed()){
                Socket socket = serverSocket.accept();

                ThreadHandler clientHandler = new ThreadHandler(socket);
                Thread thread = new Thread(clientHandler);

                thread.start();

            }
        }
        catch(IOException e){
            closeServerSocket();
        }
    }

    public void closeServerSocket() {
        try {
            if (serverSocket != null) {
                serverSocket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


}