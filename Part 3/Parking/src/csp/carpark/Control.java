package csp.carpark;

import org.jcsp.lang.Alternative;
import org.jcsp.lang.AltingChannelInputInt;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelOutputInt;
import org.jcsp.lang.Guard;

public class Control implements CSProcess{
	private AltingChannelInputInt arrive;
	private AltingChannelInputInt depart;
	private ChannelOutputInt arrive_out;
	private ChannelOutputInt depart_out;
	private final int MAX_SPACES = 10;
	private int spaces = 10;
	
	//Set up control for 2 way communications with Arrive and Depart.
	public Control(AltingChannelInputInt arrive, AltingChannelInputInt depart,
			ChannelOutputInt arrive_out, ChannelOutputInt depart_out){
		this.arrive = arrive;
		this.depart = depart;
		this.arrive_out = arrive_out;
		this.depart_out = depart_out;
	}
	
	public void run(){
		final Guard[] altChannels = {depart, arrive};
		final Alternative alt = new Alternative(altChannels);
		
		while(true){
			switch(alt.priSelect()){
//			switch(alt.fairSelect()){
			case 1:
				//arrive
				if(spaces > 0){
					//there is space so accept arrival
					arrive.read();
					spaces--;
					arrive_out.write(spaces);
				}
				break;
			case 0:
				//depart
				if(spaces < MAX_SPACES){
					//there is a car inside, so allow departure
					depart.read();
					spaces++;
					depart_out.write(spaces);
				}
				else{
					depart.read();
					depart_out.write(-1);
				}
				break;
			}
		}
	}

}
