#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *update_counter1();
void *update_counter2();

pthread_mutex_t mutex;
int counter = 0;

int main() { 
	pthread_t thread1, thread2;
	
	//initialise mutex
	pthread_mutex_init(&mutex, NULL);
	
	//create and join threads
	pthread_create(&thread1, NULL, update_counter1, NULL);
	pthread_create(&thread2, NULL, update_counter2, NULL);
	
	/* Wait for thread to complete */
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	pthread_mutex_destroy(&mutex);
	return 0;
}


void *update_counter1(){
	// lock section, increment counter 5 times, unlock section...
	pthread_mutex_lock(&mutex);
	int i;
	for (i=0; i<5; i++) {
		printf("Thread 1 counter value: %d\n", counter++);
	}
	pthread_mutex_unlock(&mutex);
}

void *update_counter2(){
	// lock section, increment counter 5 times, unlock section...
	pthread_mutex_lock(&mutex);
	int i;
	for (i=0; i<5; i++) {
		printf("Thread 2 counter value: %d\n", counter++);
	}
	pthread_mutex_unlock(&mutex);
}


/*
 The library to supply to the compiler in this case is pthread.
 In the code you created in Question 1 there should be no need to worry 
 about the synchronization of threads, as they are not trying to access 
 any shared global variables.
 If we consider the case where there is a global integer variable 
 that each thread will update, then we would need to use mutexes 
 to create a critical section of code and ensure mutual exclusion 
 within the threads while updating the variable.
 
 Complete the above code template by creating two threads that safely 
 increment the global counter (in a for-loop that iterates 5 times) 
 with synchronization using a mutex. Refer to the man pages for 
 pthread_mutex_init, pthread_mutex_lock, and pthread_mutex_unlock 
 for more information. The output of your program should be as follows:
 Thread 1 counter value: 0 
 Thread 1 counter value: 1 
 Thread 1 counter value: 2 
 Thread 1 counter value: 3 
 Thread 1 counter value: 4 
 Thread 2 counter value: 5 
 Thread 2 counter value: 6 
 Thread 2 counter value: 7 
 Thread 2 counter value: 8 
 Thread 2 counter value: 9
 */