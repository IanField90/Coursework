#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#define MESSAGE_SIZE 40

struct message {
	long int type;
	char text[MESSAGE_SIZE];
};

int main(int argc, char * argv[]){
	long id;
	struct message msg;
	
	if (msgrcv(atoi(argv[1]), &msg, sizeof(msg.text), 0, 0) != -1) {
		printf("Reading queue id %s\n", argv[1]);
		printf("Message type: %ld\n", msg.type);
		printf("Message text: %s\n", msg.text);
	}
	else {
		printf("Error reading queue.\n");
	}
	
	return 0;
}