package cspmodel.carpark;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.CSTimer;
import org.jcsp.lang.One2OneChannelInt;

public class Depart implements CSProcess{
	private One2OneChannelInt depart;
	private int value;

	public Depart(One2OneChannelInt in){
		depart = in;
	}

	@Override
	public void run() {
		while(true){
			final CSTimer tim = new CSTimer();
			if(depart.in().pending()){
				value = depart.in().read();
				System.out.println("Spaces left " + value);
			}
			tim.sleep(50);
		}
	}

}
