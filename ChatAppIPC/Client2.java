
import java.io.*;
import java.net.Socket;

public class Client2 {

	public static final String SERVER_IP="127.0.0.1";
	public static final int PORT=9090;
	
	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
        Socket socket= new Socket(SERVER_IP,PORT);
        
        BufferedReader serverResponse= new BufferedReader(new InputStreamReader(socket.getInputStream()));
        BufferedReader clientReply= new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out= new PrintWriter(socket.getOutputStream(),true);
        
        while(true)
        {
        	System.out.println("Client:");
        	String reply=clientReply.readLine();
            out.println(reply);
            if(reply.equals("quit"))
            {
            	System.out.println("Client is closing");
            	break;
            }
            
            String response=serverResponse.readLine();
            System.out.println("Server sent message : "+ response);
        }
        socket.close();
	}

}
