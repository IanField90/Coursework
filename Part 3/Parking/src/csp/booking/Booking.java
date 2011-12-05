package csp.booking;

import java.awt.Frame;
import java.awt.GridLayout;
import java.util.ArrayList;

import org.jcsp.awt.ActiveButton;
import org.jcsp.awt.ActiveClosingFrame;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.One2OneChannel;
import org.jcsp.lang.Parallel;

/**
 * 
 * @author ianfield
 * Spawn multiple 'connections (CSProcess)', 1 per user. Connection first, then operations, then disconnect
 */
public class Booking implements CSProcess {
	public Booking(One2OneChannel chan_mail, One2OneChannel chan_query) {
		// TODO Auto-generated constructor stub
	}

	public void run(){

	}
	
	/**
	 * Users ID Tracked and sent. Eg. User 1 connect, Send user 1, User 1 lookup, user 1 reserve
	 * @param argv
	 */

	public static void main(String argv[]){
		ActiveClosingFrame activeClosingFrame = new ActiveClosingFrame("Booking");
		final Frame frame = activeClosingFrame.getActiveFrame();
		
		ArrayList<Integer> users = new ArrayList<Integer>();
		int user_counter = 0;
		
		final One2OneChannel reserve_event = Channel.one2one();
		final One2OneChannel send_event = Channel.one2one();
		
		final ActiveButton btn_reserve = new ActiveButton(null, reserve_event.out(), "Reserve");		
		
		
		frame.setLayout(new GridLayout(3, 3));
		frame.add(btn_reserve);
		frame.pack();
		frame.setVisible(true);
		
		Reserve reserve_proc = new Reserve(reserve_event.in(), send_event.out());
		Send send_proc = new Send(send_event.in());
		
		
		new Parallel(new CSProcess[]{
				activeClosingFrame,
				btn_reserve,
				send_proc,
				reserve_proc
				
		}).run();
	}

}
