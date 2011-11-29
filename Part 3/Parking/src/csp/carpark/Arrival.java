package csp.carpark;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.One2OneChannelInt;

public class Arrival implements CSProcess {
	private One2OneChannelInt arrive_notify, arrive_response;
	private int car_number = 1;

	public Arrival(One2OneChannelInt arrive_notify, One2OneChannelInt arrive_response) {
		this.arrive_notify = arrive_notify;
		this.arrive_response = arrive_response;
	}

	public void run(){
		while(true){
			arrive_notify.out().write(car_number);

//			if(arrive_response.in().pending()){
				int spaces = arrive_response.in().read();
				System.out.println("Car #" + car_number + " arrives. Spaces left: " + spaces);
//			}
			car_number++;
		}
	}
}
