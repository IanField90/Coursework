package cspmodel;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.ChannelInputInt;
import org.jcsp.lang.ChannelOutputInt;
import org.jcsp.lang.One2OneChannelInt;
import org.jcsp.lang.Parallel;

public class CarPark implements CSProcess{
	One2OneChannelInt arrive = Channel.one2oneInt(); 
	One2OneChannelInt depart = Channel.one2oneInt();
	
	Parallel carpark =  new Parallel(new CSProcess[] {
			new Arrives((ChannelOutputInt) arrive),
			new Control((ChannelOutputInt)arrive, (ChannelInputInt)depart),
			new Departs((ChannelInputInt)depart)
	});
	
	public void run() {
		
	}
}