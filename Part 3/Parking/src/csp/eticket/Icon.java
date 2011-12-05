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
			icon_start.read();
			System.out.println("ICON");
			if(!launched){
				ui_start.write(1);
				launched = true;
			}
		}
	}

}
