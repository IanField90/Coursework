package csp.carpark;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.One2OneChannelInt;

public class Arrival implements CSProcess {
	private One2OneChannelInt arrive;
	private int car_number;
	
	public Arrival(One2OneChannelInt chan_arrive, int car_number) {
		this.arrive = chan_arrive;
		this.car_number = car_number;
	}

	public void run(){
		//Tell controller that car has arrived
		arrive.out().write(car_number);
		
		int response = arrive.in().read();
		
		if(response != 0){
			//Can arrive
			System.out.println("Car #" + response + " arrives");
		}
		
	}
}
