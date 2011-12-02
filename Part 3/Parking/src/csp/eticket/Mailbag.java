package csp.eticket;

import org.jcsp.lang.Alternative;
import org.jcsp.lang.AltingChannelInput;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Guard;

public class Mailbag implements CSProcess {
	private AltingChannelInput arrive_event, next_event, previous_event, delete_event, send_event, icon_start;
	public Mailbag(AltingChannelInput arrive_event, AltingChannelInput next_event,
			AltingChannelInput previous_event, AltingChannelInput delete_event,
			AltingChannelInput send_event, AltingChannelInput icon_start) {
		this.arrive_event = arrive_event;
		this.next_event = next_event;
		this.previous_event = previous_event;
		this.delete_event = delete_event;
		this.send_event = send_event;
		this.icon_start = icon_start;
	}

	public void run(){
		final Guard[] altChannels = {arrive_event, next_event, previous_event, delete_event, send_event, icon_start};
		final Alternative alt = new Alternative(altChannels);

		final int ARRIVE = 0;
		final int NEXT = 1;
		final int PREVIOUS = 2;
		final int DELETE = 3;
		final int SEND = 4;
		final int ICON = 5;

		while(true){
			switch(alt.fairSelect()){
			case ARRIVE:
				break;
			case NEXT:
				break;
			case PREVIOUS:
				break;
			case DELETE:
				break;
			case SEND:
				break;
			case ICON:
				break;
			}
		}

	}


}
