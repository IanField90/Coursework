package cspmodel;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Parallel;

public class Application {
	
	
	public static void main(String args[]){
		
		Parallel application = new Parallel(new CSProcess[]{
				new CarPark(),
				new ETicket(),
				new Booking()
		});
		
		application.run();
		
	}
}
