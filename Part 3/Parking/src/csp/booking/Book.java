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
			String user = (String) book.read();
			System.out.println(user + " Email sent!");
		}
	}
}
