package csp.booking;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.ChannelInput;
import org.jcsp.lang.ChannelOutput;
import org.jcsp.lang.One2OneChannel;
import org.jcsp.lang.ProcessManager;

public class Server implements CSProcess{
	private ChannelInput internet;
	private ChannelOutput response;
	private ChannelOutput booking;

	
	public Server(ChannelInput internet, ChannelOutput response, ChannelOutput booking){
		this.internet = internet;
		this.response = response;
		this.booking = booking;
	}
	
	@Override
	public void run() {
		while(true){
			//listen for new connection
			internet.read();
			
			//get user unique send recv channels
			One2OneChannel send = Channel.one2one();
			One2OneChannel recv = Channel.one2one();
			
			//create a session
			new ProcessManager(new Session(send.in(), recv.out(), booking)).start(); //TODO Add disconnect process
			//give user unique send/recv channels
			response.write(send.out());
			response.write(recv.in());
		}
	}

}
