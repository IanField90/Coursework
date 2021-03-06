package csp.booking;

import org.jcsp.lang.CSProcess;
import org.jcsp.lang.Channel;
import org.jcsp.lang.One2OneChannel;
import org.jcsp.lang.Parallel;
import org.jcsp.util.OverWriteOldestBuffer;

/**
 * 
 * @author ianfield
 * Spawn multiple 'connections (CSProcess)', 1 per user.
 * Connection first, then operations, then disconnect
 */
public class Booking implements CSProcess {
	public Booking(One2OneChannel chan_mail, One2OneChannel chan_query) {
		// TODO Auto-generated constructor stub
		// Would be used if fully integrating
	}

	public void run(){

	}
	
	/**
	 * Users ID Tracked and sent. Eg. User 1 connect, Send user 1, User 1 lookup, user 1 reserve
	 * @param argv
	 */

	public static void main(String argv[]){
		int max_users = 10;
		//Establish communication channels
		final One2OneChannel internet = Channel.one2one(new OverWriteOldestBuffer(max_users));
		final One2OneChannel response = Channel.one2one(new OverWriteOldestBuffer(max_users));
		final One2OneChannel booking = Channel.one2one(new OverWriteOldestBuffer(max_users));
		
		//Instantiate the server and book (emailer).
		Server server = new Server(internet.in(), response.out(), booking.out()); // creates user connections
		Book book = new Book(booking.in()); //listens then sends ETicket
		
		//Create 3 test users
		User user1 = new User(internet.out(), response.in());
		User user2 = new User(internet.out(), response.in());
		User user3 = new User(internet.out(), response.in());
				
		
		//Run all processes in parallel to prove that the Booking system is concurrent and
		//capable of multiple customer transactions simultaneously
		new Parallel(new CSProcess[]{
				server,
				book,
				user1,
				user2,
				user3
				
		}).run();
	}

}
