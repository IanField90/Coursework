package cspmodel;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.One2OneChannelInt;
import org.jcsp.lang.Parallel;

public class CarPark {

	public static void main(String args[]){

		One2OneChannelInt arrive = Channel.one2oneInt(); 
		One2OneChannelInt depart = Channel.one2oneInt();

		Parallel carpark =  new Parallel(new CSProcess[] {
				new Arrives(arrive),
				new Control(arrive, depart),
				new Departs(depart)
		});	
		carpark.run();

	}
}