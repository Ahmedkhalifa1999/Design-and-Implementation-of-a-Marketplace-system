import java.net.*;
import java.io.*;



/*
1- parsing json function and put the data in bufferReader
2-
*/
public class ThreadHandler implements Runnable {

    /*
    socket is used for starting the connection
    BufferReader contains the data from the client
    BufferWriter contains the data for the client
     */
    private Socket socket = null;
    private BufferedReader bufferedReader = null;
    private BufferedWriter bufferedWriter = null;
    //string username





    public ThreadHandler(Socket socket)
    {
        try {
            this.socket = socket;
            this.bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            this.bufferedWriter = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        }
        catch (IOException e){
            closeEverything(socket , bufferedReader , bufferedWriter);
        }
    }

    public void closeEverything(Socket socket , BufferedReader bufferedReader , BufferedWriter bufferedWriter)
    {
        try{
            if(bufferedReader != null){
                bufferedReader.close();
            }
            if(bufferedWriter != null){
                bufferedReader.close();
            }
            if(socket != null){
                socket.close();
            }

        }
        catch (IOException e){
            e.printStackTrace();
        }
    }

    @Override
    public void run()
    {
        String messageFromClient;
        // Continue to listen for messages while a connection with the client is still established.
        while (socket.isConnected()) {
            try {
                // Read what the client sent and then send it to every other client.
                messageFromClient = bufferedReader.readLine();


            }
            catch (IOException e) {
                // Close everything gracefully.
                closeEverything(socket, bufferedReader, bufferedWriter);
                break;
            }
        }
    }

}
