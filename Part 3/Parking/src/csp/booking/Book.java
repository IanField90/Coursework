package csp.booking;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;

public class Book implements CSProcess {
	private ChannelInput book;
	
	public Book(ChannelInput book){
		this.book = book;
	}
	
	public void run(){
		while(true){
			//Find out which user is booking
			String user = (String) book.read();
			//Write trace
			System.out.println(user + " Email sent!");
			//If integrating, this would trigger the arrive event in a mailbox/eticket
		}
	}
}
