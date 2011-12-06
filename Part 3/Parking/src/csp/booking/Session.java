package csp.booking;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.ChannelInput;
import org.jcsp.lang.ChannelOutput;

public class Session implements CSProcess {
	private ChannelInput request;
	private ChannelOutput response;
	private ChannelOutput book;
	
	public Session(ChannelInput request, ChannelOutput response, ChannelOutput book){
		this.request = request;
		this.response = response;
		this.book = book;
	}
	
	public void run(){
		boolean quit = false;
		System.out.println(this.toString() +" Started");
		while(!quit){
			int req_type = (Integer) request.read();
			
			switch(req_type){
			case -1:
				//Disconnect
				quit = true;
				System.out.println(this.toString() + " Disconnected");
				break;
			case 1:
				//Book
				System.out.println(this.toString() + " Booked");
				//trigger book to send email confirmation
				book.write(this.toString());

				//tell user that they have booked
				response.write(1);
				break;
			}
			
			
		}
		
	}
}
