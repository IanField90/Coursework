package csp.carpark;

import java.awt.Frame;
import java.awt.GridLayout;

import org.jcsp.awt.ActiveButton;
import org.jcsp.awt.ActiveClosingFrame;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.One2OneChannel;
import org.jcsp.lang.One2OneChannelInt;
import org.jcsp.lang.Parallel;
import org.jcsp.util.OverWriteOldestBuffer;

/**
 * 
 * @author ianfield
 * This class acts as a GUI and interface to the carpark overall.
 * Arrive and Depart events are triggered through this.
 */
public class Carpark implements CSProcess {

	public Carpark(){

	}

	public void run(){
		//TODO Auto-generated method stub
	}

	public static void main (String argv[]){
		ActiveClosingFrame activeClosingFrame = new ActiveClosingFrame("Carpark");
		final Frame frame = activeClosingFrame.getActiveFrame();
		int n = 10;// Buffer size

		final One2OneChannel arrive_event = Channel.one2one(new OverWriteOldestBuffer(n));
		final One2OneChannel depart_event = Channel.one2one(new OverWriteOldestBuffer(n));
		final One2OneChannelInt arrive = Channel.one2oneInt();
		final One2OneChannelInt depart = Channel.one2oneInt();
		final One2OneChannelInt arrive_response = Channel.one2oneInt();
		final One2OneChannelInt depart_response = Channel.one2oneInt();

		final ActiveButton btn_arrive = new ActiveButton(null, arrive_event.out(), "Arrive");
		final ActiveButton btn_depart = new ActiveButton(null, depart_event.out(), "Depart");

		Control control = new Control(arrive.in(), depart.in(), arrive_response.out(), depart_response.out());
		Arrival arrival = new Arrival(arrive_event.in(), arrive.out(), arrive_response.in());
		Departure departure = new Departure(depart_event.in(), depart.out(), depart_response.in());
		
		frame.setLayout(new GridLayout(1, 2));
		frame.add(btn_arrive);
		frame.add(btn_depart);
		frame.pack();
		frame.setVisible(true);
		
		new Parallel(new CSProcess[]{
				activeClosingFrame,
				btn_arrive,
				btn_depart,
				arrival,
				departure,
				control
		}).run();

	}

}
