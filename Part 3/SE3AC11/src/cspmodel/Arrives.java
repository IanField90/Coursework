package cspmodel;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelOutputInt;

public class Arrives implements CSProcess{
//	private One2OneChannelInt arrive;
	private ChannelOutputInt arrive;
	
	public Arrives(ChannelOutputInt out){
		arrive = out;
	}
	int value;
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		System.out.println("Arrive");
		arrive.write(new Integer(1));
	}
}
