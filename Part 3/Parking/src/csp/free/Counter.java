package csp.free;

import java.util.concurrent.atomic.AtomicLong;

public class Counter {
//	private static AtomicLong number = new AtomicLong(0);
//	public static long increment(){
//		return number.getAndIncrement();
//	}
	
	public static void main(String argv[]){
		final AtomicLong number = new AtomicLong(0);
		Thread t1 = new Thread(new Runnable(){
			public void run(){
				while(true){
					System.out.println("T1 Increment: " + number.getAndIncrement());//increment());
				}
			}
		});
		Thread t2 = new Thread(new Runnable(){
			public void run(){
				while(true){
					System.out.println("T2 Increment: " + number.getAndIncrement());//increment());
				}
			}
		});
	
		t1.start();
		t2.start();
		
	}
}
