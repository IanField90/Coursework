package csp.carpark;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.One2OneChannelInt;

public class Depart implements CSProcess {
	private One2OneChannelInt depart_notify, depart_response;

	public Depart(One2OneChannelInt depart_notify, One2OneChannelInt depart_response) {
		this.depart_notify = depart_notify;
		this.depart_response = depart_response;
	}

	public void run(){
		while(true){
			depart_notify.out().write(1);
			
			int spaces = depart_response.in().read();
			System.out.println("Spaces left: " + spaces);

//			if(depart_response.in().pending()){
//				int spaces = depart_response.in().read();
//				System.out.println("Spaces left: " + spaces);
//			}
		}
	}

}
