package csp.booking;

import java.awt.Frame;

import org.jcsp.awt.ActiveClosingFrame;
import org.jcsp.lang.CSProcess;
import org.jcsp.lang.One2OneChannel;

/**
 * 
 * @author ianfield
 * Spawn multiple 'connections', 1 per user. Connection first, then operations, then disconnect
 */
public class Booking implements CSProcess {
	public Booking(One2OneChannel chan_mail, One2OneChannel chan_query) {
		// TODO Auto-generated constructor stub
	}

	public void run(){

	}

	public static void main(String args[]){
		ActiveClosingFrame activeClosingFrame = new ActiveClosingFrame("Booking");
		Frame frame = activeClosingFrame.getActiveFrame();
		

	}

}
