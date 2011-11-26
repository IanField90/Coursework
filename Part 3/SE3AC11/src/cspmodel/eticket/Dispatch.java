package cspmodel.eticket;

import org.jcsp.lang.CSProcess;

public class Dispatch implements CSProcess {
	
	public Dispatch(){
		
	}
	
	public void run(){
		//TODO If pending message
		System.out.println("Message Dispatched");
	}
}
