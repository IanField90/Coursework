package csp.carpark;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.One2OneChannel;
import org.jcsp.lang.One2OneChannelInt;
import org.jcsp.lang.Parallel;

public class Carpark implements CSProcess {
	private Arrival arrival;
	private Depart depart;
	private Control control;
	private JFrame frame = new JFrame("Car Park");
	
	public Carpark(One2OneChannel chan_ticket){		
		One2OneChannelInt arrive_notify = Channel.one2oneInt();
		One2OneChannelInt arrive_response = Channel.one2oneInt();
		One2OneChannelInt depart_notify = Channel.one2oneInt();
		One2OneChannelInt depart_response = Channel.one2oneInt();
		
		this.arrival = new Arrival(arrive_notify, arrive_response);
		this.depart = new Depart(depart_notify, depart_response);
		this.control = new Control(arrive_notify, arrive_response, depart_notify, depart_response);
	}
	
	public void run(){
		
		Parallel carpark = new Parallel(new CSProcess[]{
				arrival,
				control,
				depart
		});
		
		carpark.run();
	}
	
	public void createAndShowGUI(){
		if(!frame.isVisible()){
			JPanel carpark = new JPanel();
			carpark.add(new JTextField("Hello"));
			frame.add(carpark);
			frame.pack();
			frame.setVisible(true);
			frame.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
		}
		else{
			frame.setVisible(true);
		}
		
	}
	
	public static void main (String argv[]){
		One2OneChannelInt arrive_notify = Channel.one2oneInt();
		One2OneChannelInt arrive_response = Channel.one2oneInt();
		One2OneChannelInt depart_notify = Channel.one2oneInt();
		One2OneChannelInt depart_response = Channel.one2oneInt();

		Parallel carpark = new Parallel(new CSProcess[]{
				new Arrival(arrive_notify, arrive_response),
				new Depart(depart_notify, depart_response),
				new Control(arrive_notify, arrive_response, depart_notify, depart_response)
		});
		carpark.run();
	}

}
