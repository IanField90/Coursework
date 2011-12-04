package csp.carpark;

import org.jcsp.lang.AltingChannelInput;
import org.jcsp.lang.AltingChannelInputInt;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelOutputInt;

public class Departure implements CSProcess {
	private AltingChannelInput depart_event;
	private ChannelOutputInt departure;
	private AltingChannelInputInt depart_response;
	
	public Departure(AltingChannelInput depart_event, ChannelOutputInt departure,
			AltingChannelInputInt depart_response){
		this.depart_event = depart_event;
		this.departure = departure;
		this.depart_response = depart_response;
	}

	public void run(){
		
		while(true){
			if(depart_event.pending()){
				depart_event.read();
				departure.write(1);
				
				int spaces = depart_response.read();
				// -1 passed to stop busy waiting if no cars in car park
				if(spaces != -1){
					System.out.println("Departure. Spaces left: " + spaces);
				}else{
					System.out.println("No cars in car park");
				}
			}
		}
		
	}

}
