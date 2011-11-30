package csp.eticket;

import java.awt.Frame;
import java.awt.GridLayout;

import org.jcsp.awt.ActiveButton;
import org.jcsp.awt.ActiveClosingFrame;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.One2OneChannel;
import org.jcsp.util.OverWriteOldestBuffer;

public class ETicket implements CSProcess{
	
	
	public ETicket(One2OneChannel chan_mail) {
		// TODO Auto-generated constructor stub
	}
	
	public ETicket(){
		
	}
	public void run(){
		
	}
	
	public static void main(String argv[]){
		ActiveClosingFrame activeClosingFrame = new ActiveClosingFrame("E-Ticket");
		final Frame frame = activeClosingFrame.getActiveFrame();
		int n = 10; //Buffer size
		
		final One2OneChannel arrive_event = Channel.one2one(new OverWriteOldestBuffer(n));
		final One2OneChannel icon_event = Channel.one2one();
		final One2OneChannel next_event = Channel.one2one();
		final One2OneChannel previous_event = Channel.one2one();
		final One2OneChannel delete_event = Channel.one2one();
		final One2OneChannel send_event = Channel.one2one(); //triggers dispatch
		final One2OneChannel send = Channel.one2one();// send -> DISPATCH
		
		final ActiveButton btn_arrive_event = new ActiveButton(null, arrive_event.out(), "Arrive");
		final ActiveButton btn_icon_event = new ActiveButton(null, icon_event.out(), "ICON");
		final ActiveButton btn_next_event = new ActiveButton(null, next_event.out(), "Next");
		final ActiveButton btn_previous_event = new ActiveButton(null, previous_event.out(), "Previous");
		final ActiveButton btn_delete_event = new ActiveButton(null, delete_event.out(), "Delete");
		final ActiveButton btn_send_event = new ActiveButton(null, send_event.out(), "Send");
		
		
		frame.setLayout(new GridLayout(2, 3));
		frame.add(btn_arrive_event);
		frame.add(btn_icon_event);

		frame.add(btn_send_event);
		frame.add(btn_next_event);
		frame.add(btn_previous_event);
		frame.add(btn_delete_event);
		frame.pack();
		frame.setVisible(true);
		
	}


}
