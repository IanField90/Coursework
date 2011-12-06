package csp.eticket;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;
import org.jcsp.lang.ChannelOutput;

public class Icon implements CSProcess {

	private ChannelInput icon_start;
	private ChannelOutput ui_start;
	public Icon(ChannelInput icon_start, ChannelOutput ui_start) {
		this.icon_start = icon_start;
		this.ui_start = ui_start;
	}

	public void run(){
		boolean launched = false;
		while(true){
			//Read to see if the icon is pressed
			icon_start.read();
			//Write trace as icon has been pressed
			System.out.println("ICON");
			//prevent multiple UI launching.
			if(!launched){
				ui_start.write(1);
				launched = true;
			}
		}
	}

}
