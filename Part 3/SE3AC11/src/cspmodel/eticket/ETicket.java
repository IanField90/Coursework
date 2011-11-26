package cspmodel.eticket;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Parallel;

public class ETicket implements CSProcess{
//	private One2OneChannel
	
	public ETicket(){
		
	}
	
	public void run(){
		
		Parallel eticket = new Parallel(new CSProcess[]{
				new MailBag(),
				new UInt(),
				new Dispatch()
		});
		
	}
}
