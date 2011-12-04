package csp.booking;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;

public class Lookup implements CSProcess {
	private ChannelInput lookup;
	
	public Lookup(ChannelInput lookup){
		this.lookup = lookup;
	}
	
	public void run(){
		while(true){
			int user = (Integer) lookup.read();
			System.out.println("User " + user + " looked up");
		}
	}
}
