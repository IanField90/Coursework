package csp.carpark;

import org.jcsp.lang.Alternative;
import org.jcsp.lang.AltingChannelInput;
import org.jcsp.lang.AltingChannelInputInt;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.CSTimer;
import org.jcsp.lang.ChannelOutputInt;
import org.jcsp.lang.Guard;
import org.jcsp.lang.One2OneChannelInt;

public class Arrival implements CSProcess {
	private AltingChannelInput arrival_event;
	private ChannelOutputInt arrive;
	private AltingChannelInputInt arrive_response;
	private int car_number = 1;

	public Arrival(AltingChannelInput arrival_event, ChannelOutputInt arrive,
			AltingChannelInputInt arrive_response) {
		// TODO Auto-generated constructor stub
		this.arrival_event = arrival_event;
		this.arrive = arrive;
		this.arrive_response = arrive_response;
		
	}

	public void run(){	
		CSTimer tim = new CSTimer();
		final Guard[] altChans = {};
		final Alternative alt = new Alternative(altChans);
		while(true){

			//If arrival event is triggered
			if(arrival_event.pending()){
				arrival_event.read();
//				System.out.println("Arrival event received");
				
				arrive.write(car_number);
				int spaces = arrive_response.read();//TODO make not lock
				System.out.println("Car #" + car_number + " Arrive. Spaces left: " + spaces);
				car_number++;
			}

		}
	}
}
