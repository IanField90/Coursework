package csp.eticket;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;

public class Dispatch implements CSProcess {

	private ChannelInput send;
	
	public Dispatch(ChannelInput send) {
		this.send = send;
	}

	public void run(){
		while (true){
			
				send.read();
				System.out.println("SEND Dispatch");
			
		}
		
	}
}
