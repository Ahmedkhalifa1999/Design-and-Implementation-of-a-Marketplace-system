import java.nio.channels.AsynchronousSocketChannel;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;


/*
1- parsing json function and put the data in bufferReader
2-
/
public class ClientHandler implements Runnable {

    /
    socket is used for starting the connection
    BufferReader contains the data from the client
    BufferWriter contains the data for the client
    */
private final Future<AsynchronousSocketChannel> socket;

public ClientHandler(Future<AsynchronousSocketChannel> socket)
        {
        this.socket = socket;
        }

public void closeEverything(Future<AsynchronousSocketChannel> socket)
        {

        if(socket != null){
        boolean flag;
        flag = socket.cancel(true);
        }

        }

@Override
public void run()
        {
        // Continue to listen for messages while a connection with the client is still established.
        while (true) {
        try {
        // Read what the client sent and then send it to every other client.
        AsynchronousSocketChannel data = socket.get();

        if(socket.isCancelled() || socket.isDone()){ break; }


        }
        catch (InterruptedException | ExecutionException e) {
        // Close everything gracefully.
        closeEverything(socket);
        break;
        }
        }
        }

        }