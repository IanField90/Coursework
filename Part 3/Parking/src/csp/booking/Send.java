package csp.booking;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;
import org.jcsp.lang.ChannelOutput;

public class Send implements CSProcess{
	private ChannelInput send;
	private ChannelOutput send_confirm;
	public Send(ChannelInput send, ChannelOutput send_confirm){
		this.send = send;
		this.send_confirm = send_confirm;
	}
	
	public void run(){
		while(true){
			send.read();
			System.out.println("Send Booking");
			send_confirm.write(1);
		}
	}
}
