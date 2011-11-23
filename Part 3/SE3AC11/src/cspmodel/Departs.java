package cspmodel;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInputInt;

public class Departs implements CSProcess{
	private ChannelInputInt depart;
	private int value;

	public Departs(ChannelInputInt in){
		depart = in;
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		value = depart.read();
		System.out.println("Spaces left " + value);
	}

}
