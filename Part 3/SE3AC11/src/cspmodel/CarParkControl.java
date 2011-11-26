package cspmodel;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.CSTimer;
import org.jcsp.lang.One2OneChannelInt;

public class CarParkControl implements CSProcess{
	private One2OneChannelInt arrive;
	private One2OneChannelInt depart;
	private static final int MAX_SPACES = 50;
	private int spaces;


	public CarParkControl(One2OneChannelInt arrive, One2OneChannelInt depart){
		this.arrive = arrive;
		this.depart = depart;
		spaces = MAX_SPACES;
	}

	public void run() {
		final CSTimer tim = new CSTimer();
		while(true){
			if(arrive.in().pending()){
				int car = arrive.in().read();
				if(spaces > 0){
					//can let another car in
					spaces--;
					System.out.println("Car #" + car +" in");
				}
			}
			
			if(spaces < MAX_SPACES){
				//care leaves, more space
				spaces++;
				depart.out().write(spaces);
			}
			tim.sleep(50);
		}

	}
}
