package csp.booking;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;

public class Send implements CSProcess{
	private ChannelInput send;
	public Send(ChannelInput send){
		this.send = send;
	}
	
	public void run(){
		while(true){
			send.read();
			System.out.println("Send Booking");
		}
	}
}
