package cspmodel;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.CSTimer;
import org.jcsp.lang.One2OneChannelInt;

public class Arrives implements CSProcess{
	private One2OneChannelInt arrive;
	private int car;
	public Arrives(One2OneChannelInt out){
		arrive = out;
		car = 0;
	}

	@Override
	public void run() {
		while(true){
			final CSTimer tim = new CSTimer();
			System.out.println("Car #" + ++car + " arrives");
			arrive.out().write(car);
			tim.sleep(50);
		}
	}
}
