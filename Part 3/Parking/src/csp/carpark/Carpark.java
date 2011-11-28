package csp.carpark;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.One2OneChannel;
import org.jcsp.lang.Parallel;

public class Carpark implements CSProcess {
	private Arrival arrival;
	private Depart depart;
	private Control control;
	private JFrame frame = new JFrame("Car Park");
	
	public Carpark(One2OneChannel chan_ticket){		
		One2OneChannel arrive = Channel.one2one();
		One2OneChannel depart = Channel.one2one();
		
		this.arrival = new Arrival(arrive, 1);
		this.depart = new Depart(depart);
		this.control = new Control(arrive, depart);
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

}
