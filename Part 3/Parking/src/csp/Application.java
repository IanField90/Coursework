package csp;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JPanel;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.One2OneChannelInt;
import org.jcsp.lang.Parallel;

import csp.booking.Booking;
import csp.carpark.Carpark;
import csp.eticket.ETicket;

public class Application extends JPanel implements ActionListener{
	private static Carpark carpark;
	private static Booking booking;
	private static ETicket eticket;
	private static One2OneChannelInt arrive, depart, booking_check;
	
	public static void main(String args[]){
		arrive = Channel.one2oneInt();
		depart = Channel.one2oneInt();
		booking_check = Channel.one2oneInt();
		
		carpark = new Carpark(arrive, depart, booking_check);
		booking = new Booking();
		eticket = new ETicket();
		
		
		Parallel application = new Parallel(new CSProcess[]{
			booking,
			carpark,
			eticket
		});
		
		application.run();
		
		final Application app = new Application();
		javax.swing.SwingUtilities.invokeLater(new Runnable(){
			public void run(){
				app.createAndShowGUI();
			}
		});
	}
	
	public void createAndShowGUI(){
		JFrame frame = new JFrame("Application");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		
	}
}
