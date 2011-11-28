package csp.booking;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.One2OneChannel;

public class Booking implements CSProcess, ActionListener {
	private JFrame frame = new JFrame("Booking");		

	public Booking(One2OneChannel chan_mail, One2OneChannel chan_query) {
		// TODO Auto-generated constructor stub
	}

	public void run(){

	}

	public void createAndShowGUI(){
		if(!frame.isVisible()){
			frame.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
			JPanel booking = new JPanel();
			booking.setLayout(new GridLayout(5, 2));
			JTextField txt_day, txt_month, txt_year, txt_length;
			txt_day = new JTextField();
			txt_month = new JTextField();
			txt_year = new JTextField();
			txt_length = new JTextField();
			booking.add(new JLabel("Day:"));
			booking.add(txt_day);
			booking.add(new JLabel("Month:"));
			booking.add(txt_month);
			booking.add(new JLabel("Year:"));
			booking.add(txt_year);
			txt_year.setText("2011");
			txt_year.setEditable(false);
			booking.add(new JLabel("Length:"));
			booking.add(txt_length);

			JButton book = new JButton("Book");
			book.addActionListener(this);
			booking.add(book);
			frame.add(booking);
			frame.pack();
			frame.setVisible(true);
		}
		else{
			frame.setVisible(true);
		}
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	//	public static void main(String args[]){
	//		createAndShowGUI();
	//	}

}
