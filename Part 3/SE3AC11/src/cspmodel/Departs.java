package cspmodel;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.One2OneChannelInt;

public class Departs implements CSProcess{
	private One2OneChannelInt depart;
	private int value;

	public Departs(One2OneChannelInt in){
		depart = in;
	}

	@Override
	public void run() {
		while(true){
			if(depart.in().pending()){
				value = depart.in().read();
				System.out.println("Spaces left " + value);
			}
		}
	}

}
