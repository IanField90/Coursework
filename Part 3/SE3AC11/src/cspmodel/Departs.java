package cspmodel;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInputInt;

public class Departs implements CSProcess{
	private ChannelInputInt depart;
	public Departs(ChannelInputInt in){
		depart = in;
	}
	int value;
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		while(true){
			value = depart.read();
			System.out.println("Spaces left "+ value);
		}
	}

}
