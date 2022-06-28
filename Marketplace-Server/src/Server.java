import java.io.IOException;
import java.nio.channels.AsynchronousServerSocketChannel;
import java.nio.channels.AsynchronousSocketChannel;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;


public class Server implements Runnable{
    /*
    1- ServerSocket is the port number where the connection will be established
    2- The Server starts the connection
    3- by taking the data to the client handler to handle and parsing the request given by the user
    4- Every request from the user will make a thread
    5- After finishing the connection go to closeServerSocket.
    */
    private final AsynchronousServerSocketChannel serverSocket;


    ExecutorService Thread = Executors.newFixedThreadPool(8);





    public Server(AsynchronousServerSocketChannel RequestSocket)
    {
        this.serverSocket = OpenConnection(RequestSocket);

    }

    public AsynchronousServerSocketChannel OpenConnection(AsynchronousServerSocketChannel RequestSocket)
    {
        try{
            // open the server socket and bind it with the address of the client
            RequestSocket =  AsynchronousServerSocketChannel.open().bind(RequestSocket.getLocalAddress());


        }
        catch (IOException e){
            closeServerSocket();
        }

        return RequestSocket;
    }


    public void StartServer()
    {
        while(this.serverSocket.isOpen())
        {

            Future<AsynchronousSocketChannel> socket =  serverSocket.accept();
            //AsynchronousSocketChannel connection = socket.get();

            Thread.execute(new ClientHandler(socket));

        }
    }

    public void closeServerSocket() {
        try {
            if (this.serverSocket != null) {
                this.serverSocket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    @Override
    public void run() {




    }



}