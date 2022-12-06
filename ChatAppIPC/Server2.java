import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Server2 {
    private static final int PORT=9090;
    private static ArrayList<ClientHandler>clients= new ArrayList<>();
    private static ExecutorService pool=Executors.newFixedThreadPool(4);  
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
        ServerSocket listener= new ServerSocket(PORT);
        
        while(true) {
        	System.out.println("Server is waiting for connection......");
            Socket client=listener.accept();
            System.out.println("Server is connected to client");
            ClientHandler clientThread=new ClientHandler(client,clients);
            clients.add(clientThread);
            pool.execute(clientThread);
        }
     
        
      
        
	}

}
