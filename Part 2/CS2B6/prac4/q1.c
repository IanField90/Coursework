#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message1(); 
void *print_message2();

int main() { 
	pthread_t thread1, thread2;
	// Create and join threads 1 & 2... 
	pthread_create(&thread1, NULL, print_message1, NULL);
	pthread_create(&thread2, NULL, print_message2, NULL);
	
	/* Wait for thread to complete */
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	return 0;
}

void *print_message1(){ 
	printf("Hello from Thread1\n"); 
}

void *print_message2(){
	printf("Hello from Thread2\n");
}

/*
 Create a program where two threads of execution are generated 
 with the pthread_create API call
 
 Each thread should print a different message, as indicated above. 
 Look at the man pages for pthread_create and pthread_join for help. 
 The output from your program should be as follows:
 Hello from Thread1 Hello from Thread2
 The library to supply to the compiler in this case is pthread.
*/