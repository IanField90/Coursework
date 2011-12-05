package csp.eticket;

import org.jcsp.lang.AltingChannelInput;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;

public class UserInterface implements CSProcess{
	private ChannelInput ui_start;
	public UserInterface(AltingChannelInput ui_start){
		this.ui_start = ui_start;
	}
	
	public void run(){
		ui_start.read();
		System.out.println("User Interface launched");

	}
}
