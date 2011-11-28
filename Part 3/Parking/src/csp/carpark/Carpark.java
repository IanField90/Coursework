package csp.carpark;

import javax.swing.JPanel;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.One2OneChannelInt;
import org.jcsp.lang.Parallel;

public class Carpark extends JPanel implements CSProcess {
	private Arrival arrival;
	private Depart depart;
	private Control control;
	
	
	public Carpark(One2OneChannelInt arrive, One2OneChannelInt depart, One2OneChannelInt booking){
		this.arrival = new Arrival(arrive, 1);
		this.depart = new Depart(depart);
		this.control = new Control(arrive, depart, booking);
	}
	
	public void run(){
		
		Parallel carpark = new Parallel(new CSProcess[]{
				arrival,
				control,
				depart
		});
		
		carpark.run();
	}

}
