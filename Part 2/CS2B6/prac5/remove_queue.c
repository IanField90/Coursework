#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	if (argc == 2) {
		msgctl(atoi(argv[1]), IPC_RMID, NULL);
		printf("Queue %d removed\n", atoi(argv[1]));
	}
	else {
		printf("Expected argument: Queue\n");
	}
	return 0;
}