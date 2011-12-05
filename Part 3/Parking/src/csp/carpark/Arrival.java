package csp.carpark;

import org.jcsp.lang.AltingChannelInput;
import org.jcsp.lang.AltingChannelInputInt;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelOutputInt;

public class Arrival implements CSProcess {
	private AltingChannelInput arrival_event;
	private ChannelOutputInt arrive;
	private AltingChannelInputInt arrive_response;
	private int car_number = 1;

	public Arrival(AltingChannelInput arrival_event, ChannelOutputInt arrive,
			AltingChannelInputInt arrive_response) {
		this.arrival_event = arrival_event;
		this.arrive = arrive;
		this.arrive_response = arrive_response;
	}

	public void run(){	
		while(true){

			//If arrival event is triggered
			if(arrival_event.pending()){
				arrival_event.read();
				
				arrive.write(car_number);
				int spaces = arrive_response.read();
				//Remove check for Lock free (queue, [buffer])
				if(spaces != -1){
					System.out.println("Car arrive");// + car_number + " Arrive. Spaces left: " + spaces);
				}
				else{
					System.out.println("No space in carpark");
				}
				car_number++;
			}

		}
	}
}
