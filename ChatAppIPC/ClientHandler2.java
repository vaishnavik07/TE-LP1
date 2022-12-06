
import java.io.*;
import java.net.*;
import java.util.*;

public class ClientHandler2 implements Runnable{

	private Socket client;
	private ArrayList<ClientHandler2>clients;
	private BufferedReader clientReply;
//	private BufferedReader serverResponse;
	private PrintWriter out;
	
	public ClientHandler2(Socket client,ArrayList<ClientHandler2>clients) throws IOException{
		this.client=client;
		this.clients=clients;
		try {
			this.clientReply=new BufferedReader(new InputStreamReader(client.getInputStream()));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		this.out=new PrintWriter(client.getOutputStream(),true);
	}
	
	public static void main(String[] args){
		// TODO Auto-generated method stub
	}

	@Override
	public void run()
	{
		try {
		 while(true)
        {
        	String reply;
			reply=clientReply.readLine();
			if(reply.equals("quit"))
        	{
        		System.out.println("Server closing");
        		break;
        	}
			System.out.println("Client: "+reply);
			System.out.println("Send ok");
        	out.println("ServerResponse"+reply);
        }
		} catch (IOException e) {
//			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
