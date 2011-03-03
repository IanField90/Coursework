#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MESSAGE_SIZE 40

struct message {
	long int type;
	char text[MESSAGE_SIZE];
};

int main(int argc, char * argv[]){
	long int id = atoi(argv[1]);
	int i = 0;
	char msg[MESSAGE_SIZE];
	char ch;
	struct message Message;
	int sendRes;
	
	printf("Enter message to post: ");
	while ((ch = getchar()) != '\n' && i < MESSAGE_SIZE) {
		msg[i] = ch;
		i++;
	}
	msg[i] = 0; /* zero terminated string */
	
	Message.type = 1110;
	strcpy(Message.text, msg);
	
	sendRes = msgsnd(id, &Message, sizeof(struct message) - sizeof(long), 0);
	if (sendRes == 0) {
		printf("Message posted.\n");
	}
	else {
		printf("Message post failed.\n");
	}

	return 0;
}