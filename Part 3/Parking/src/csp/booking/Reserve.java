package csp.booking;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;
import org.jcsp.lang.ChannelOutput;

public class Reserve implements CSProcess{
	private ChannelInput reserve;
	private ChannelOutput send;
	
	public Reserve(ChannelInput connect, ChannelOutput send){
		this.reserve = connect;
		this.send = send;
	}
	
	public void run(){
		while(true){
			int user = (Integer) reserve.read();
			System.out.println("User " + user + " reserved");
			send.write((Integer)user);
		}
	}
}
