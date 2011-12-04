package csp.booking;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;

public class Connect implements CSProcess{
	private ChannelInput connect;
	
	public Connect(ChannelInput connect){
		this.connect = connect;
	}
	
	public void run(){
		while(true){
			int user = (Integer) connect.read();
			System.out.println("User " + user + " connected");
		}
	}
}
