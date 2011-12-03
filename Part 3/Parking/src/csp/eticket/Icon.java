package csp.eticket;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;

public class Icon implements CSProcess {

	private ChannelInput icon_start;
	public Icon(ChannelInput icon_start) {
		this.icon_start = icon_start;
	}
	
	public void run(){
		while(true){
			icon_start.read();
			System.out.println("ICON");
		}
	}

}
