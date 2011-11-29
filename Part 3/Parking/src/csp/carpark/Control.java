package csp.carpark;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.One2OneChannelInt;

public class Control implements CSProcess{
	private One2OneChannelInt arrive_notify, arrive_response, depart_notify, depart_response;
	private final int MAX_SPACES = 50;
	private int spaces = 50;

	public Control(One2OneChannelInt arrive_notify, One2OneChannelInt arrive_response, 
			One2OneChannelInt depart_notify, One2OneChannelInt depart_response) {
		this.arrive_notify = arrive_notify;
		this.arrive_response = arrive_response;
		this.depart_notify = depart_notify;
		this.depart_response = depart_response;
	}

	public void run(){
		while(true){
			
			//TODO prioritise depart over arrive but alternate guards
			
			arrive_notify.in().read();
			if(spaces > 0){
				spaces--;
				arrive_response.out().write(spaces);
			}
			
			depart_notify.in().read();
			if(spaces < MAX_SPACES){
				spaces++;
				depart_response.out().write(spaces);
			}
			
//			if(arrive_notify.in().pending()){
//				int car = arrive_notify.in().read();
//				if(spaces > 0){
//					spaces--;
//					arrive_response.out().write(spaces);
//					//					System.out.println("Car #" + car + " Arrives. Spaces left: " + spaces);
//				}
//			}
//
//			if(depart_notify.in().pending()){
//				if(spaces < MAX_SPACES){
//					spaces++;
//					depart_response.out().write(spaces);
//				}
//			}
		}
	}

}
