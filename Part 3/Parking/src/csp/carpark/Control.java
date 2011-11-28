package csp.carpark;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.One2OneChannelInt;

public class Control implements CSProcess{
	private One2OneChannelInt arrive, depart, booking;
	private final int MAX_SPACES = 50;
	public Control(One2OneChannelInt arrive, One2OneChannelInt depart, One2OneChannelInt booking) {
		this.arrive = arrive;
		this.depart = depart;
		this.booking = booking;
	}
	
	public void run(){
		while(true){
			if(arrive.in().pending()){
				
			}
			
			
		}
	}

}
