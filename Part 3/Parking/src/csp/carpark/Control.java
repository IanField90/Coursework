package csp.carpark;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.One2OneChannel;

public class Control implements CSProcess{
	private One2OneChannel arrive, depart;
	private final int MAX_SPACES = 50;
	private int spaces;
	
	public Control(One2OneChannel arrive, One2OneChannel depart) {
		this.arrive = arrive;
		this.depart = depart;
	}

	public void run(){
		while(true){
			if(arrive.in().pending()){
				if(spaces > 0){
					
				}
			}
			
			if(depart.in().pending()){
				if(spaces < MAX_SPACES){
					
				}
			}
		}
	}

}
