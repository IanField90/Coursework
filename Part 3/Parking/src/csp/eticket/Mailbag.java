package csp.eticket;

import org.jcsp.lang.Alternative;
import org.jcsp.lang.AltingChannelInput;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelOutput;
import org.jcsp.lang.Guard;

public class Mailbag implements CSProcess {
	private AltingChannelInput arrive_event, next_event, previous_event, delete_event, send_event, icon_event;
	private ChannelOutput send;
	private ChannelOutput icon_start;
	private int num_messages;

	public Mailbag(AltingChannelInput arrive_event, AltingChannelInput next_event,
			AltingChannelInput previous_event, AltingChannelInput delete_event,
			AltingChannelInput send_event, AltingChannelInput icon_event, ChannelOutput send, ChannelOutput icon_start) {
		this.arrive_event = arrive_event;
		this.next_event = next_event;
		this.previous_event = previous_event;
		this.delete_event = delete_event;
		this.send_event = send_event;
		this.icon_event = icon_event;
		this.send = send;
		this.icon_start = icon_start;
		this.num_messages = 0;
	}

	public void run(){
		final Guard[] altChannels = {arrive_event, next_event, previous_event, delete_event, send_event, icon_event};
		final Alternative alt = new Alternative(altChannels);

		final int ARRIVE = 0;
		final int NEXT = 1;
		final int PREVIOUS = 2;
		final int DELETE = 3;
		final int SEND = 4;
		final int ICON = 5;

		boolean icon_clicked = false;
		
		//Ensure prefix closed. Icon must occur first (but arrive can happen at any time).

		while(true){
			switch(alt.fairSelect()){
			case ARRIVE:
				arrive_event.read();
//				if(icon_clicked){
					System.out.println("Arrive");
					num_messages++;
//				}
				break;
			case NEXT:
				next_event.read();
				if(icon_clicked){
					if(num_messages > 1){
						System.out.println("Next");
					}
				}
				break;
			case PREVIOUS:
				previous_event.read();
				if(icon_clicked){
					if(num_messages > 1){
						System.out.println("Previous");
					}
				}
				break;
			case DELETE:
				delete_event.read();
				if(icon_clicked){
					if(num_messages > 0){
						num_messages--;
						System.out.println("Delete Message");
					}
				}
				break;
			case SEND:
				send_event.read();
				if(icon_clicked){
					send.write(1);
				}
				break;
			case ICON:
				icon_event.read();
				icon_clicked = true;
				icon_start.write(1);
				break;
			}
		}

	}


}
