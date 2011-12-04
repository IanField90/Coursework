package csp.booking;

import java.awt.Frame;

import org.jcsp.awt.ActiveClosingFrame;
import org.jcsp.lang.CSProcess;
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

	public static void main(String argv[]){
		ActiveClosingFrame activeClosingFrame = new ActiveClosingFrame("Booking");
		Frame frame = activeClosingFrame.getActiveFrame();
		
		
		

		
		frame.pack();
		frame.setVisible(true);
		
		new Parallel(new CSProcess[]{
				activeClosingFrame
				
		}).run();
	}

}
