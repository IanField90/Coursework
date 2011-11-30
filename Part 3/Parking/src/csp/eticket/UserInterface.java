package csp.eticket;

import org.jcsp.lang.AltingChannelInput;
import org.jcsp.lang.CSProcess;

public class UserInterface implements CSProcess{
	private AltingChannelInput icon_event;
	public UserInterface(AltingChannelInput icon_event){
		this.icon_event = icon_event;
	}
	
	public void run(){
		while(true){
			if(icon_event.pending()){
				icon_event.read();
				System.out.println("User Interface launched");
			}
		}
	}
}
