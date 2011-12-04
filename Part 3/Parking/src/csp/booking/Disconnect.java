package csp.booking;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;

public class Disconnect implements CSProcess{
	private ChannelInput disconnect;
	
	public Disconnect(ChannelInput disconnect){
		this.disconnect = disconnect;
	}
	
	public void run(){
		while(true){
			int user = (Integer) disconnect.read();
			System.out.println("User " + user + " disconnected");
		}
	}
}
