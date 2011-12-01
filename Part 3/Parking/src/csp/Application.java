package csp;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.One2OneChannel;
import org.jcsp.lang.Parallel;

import csp.booking.Booking;
import csp.carpark.Carpark;
import csp.eticket.ETicket;

@SuppressWarnings("serial")
public class Application extends JPanel implements ActionListener{
	private static Carpark carpark;
	private static Booking booking;
	private static ETicket eticket;
	private static One2OneChannel chan_mail, chan_ticket;
	private JButton btn_booking = new JButton("Booking");
	private JButton btn_eticket = new JButton("E-Ticket");
	private JButton btn_carpark = new JButton("Car Park");
	
	public static void main(String args[]){
		
		chan_mail = Channel.one2one();
		chan_ticket = Channel.one2one();
		
		booking = new Booking(chan_mail, chan_ticket); // booking on the day for X days
//		carpark = new Carpark(chan_ticket);
		carpark = new Carpark();
		eticket = new ETicket(chan_mail);
				
		final Parallel application = new Parallel(new CSProcess[]{
			booking,
			carpark,
			eticket
		});

		final Application app = new Application();
		SwingUtilities.invokeLater(new Runnable(){
			public void run(){
				app.createAndShowGUI();
//				application.run();

			}

		});

	}
	
	public void createAndShowGUI(){
		JFrame frame = new JFrame("Application");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Application panel = new Application();
		panel.setLayout(new GridLayout(1, 4));
		btn_booking.addActionListener(this);
		btn_eticket.addActionListener(this);
		btn_carpark.addActionListener(this);
		panel.add(btn_booking);
		panel.add(btn_eticket);
		panel.add(btn_carpark);
		frame.add(panel);
		frame.pack();
		frame.setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if(e.getSource() == btn_booking){
//			booking.main(null);
		}
		
		if(e.getSource() == btn_carpark){
//			carpark.createAndShowGUI();
			SwingUtilities.invokeLater(new Runnable(){
				public void run(){
					Carpark.main(null);
				}
			});
//			Carpark.main(null);
		}
		
		if(e.getSource() == btn_eticket){
			eticket.main(null);
		}
		
	}
}
