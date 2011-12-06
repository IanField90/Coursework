package csp.booking;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;
import org.jcsp.lang.ChannelOutput;

public class User implements CSProcess{
	private ChannelOutput internet;
	private ChannelInput response;
	
	public User(ChannelOutput internet, ChannelInput response){
		this.internet = internet;
		this.response = response;
	}
	
	public void run(){
		internet.write(1);
		
		//get the two communication channels from the server for
		//duration of session, once a user sends disconnect, the
		//session is destroyed (CSProcess run has completed for Session)
		ChannelOutput out = (ChannelOutput) response.read();
		ChannelInput in = (ChannelInput) response.read();
		
		//Wrtie trace for user connection
		System.out.println(this.toString() + " Connected");
		
		out.write(1); //Book
		in.read();// Confirmation
		out.write(-1); //disconnect
		
	}
}
