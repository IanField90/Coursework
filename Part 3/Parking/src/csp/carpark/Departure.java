package csp.carpark;

import org.jcsp.lang.AltingChannelInput;
import org.jcsp.lang.AltingChannelInputInt;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelOutputInt;

public class Departure implements CSProcess {
//	private One2OneChannelInt depart_notify, depart_response;
//
//	public Depart(One2OneChannelInt depart_notify, One2OneChannelInt depart_response) {
//		this.depart_notify = depart_notify;
//		this.depart_response = depart_response;
//	}
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
				if(spaces != -1){
					System.out.println("Departure. Spaces left: " + spaces);
				}
			}
		}
		
//		while(true){
//			depart_notify.out().write(1);
//			
//			int spaces = depart_response.in().read();
//			System.out.println("Spaces left: " + spaces);

//			if(depart_response.in().pending()){
//				int spaces = depart_response.in().read();
//				System.out.println("Spaces left: " + spaces);
//			}
//		}
	}

}
