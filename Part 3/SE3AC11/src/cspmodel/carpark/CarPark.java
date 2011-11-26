package cspmodel.carpark;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.One2OneChannelInt;
import org.jcsp.lang.Parallel;

public class CarPark implements CSProcess{

//	public static void main(String args[]){
//
//		One2OneChannelInt arrive = Channel.one2oneInt(); 
//		One2OneChannelInt depart = Channel.one2oneInt();
//
//		Parallel carpark =  new Parallel(new CSProcess[] {
//				new CarParkArrival(arrive),
//				new CarParkControl(arrive, depart),
//				new CarParkDeparture(depart)
//		});	
//		carpark.run();
//	}
	
	public void run(){
		One2OneChannelInt arrive = Channel.one2oneInt(); 
		One2OneChannelInt depart = Channel.one2oneInt();

		Parallel carpark =  new Parallel(new CSProcess[] {
				new Arrive(arrive),
				new Control(arrive, depart),
				new Depart(depart)
		});	
		carpark.run();
	}
}