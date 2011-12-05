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
		
		ChannelOutput out = (ChannelOutput) response.read();
		ChannelInput in = (ChannelInput) response.read();
		
		out.write(1); //Book
		in.read();// Confirmation
		out.write(-1); //disconnect
		
	}
}
