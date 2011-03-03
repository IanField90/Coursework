#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>

int main(){
	long id;
	struct msqid_ds *info;
	int rtnVal;
	
	id = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
	if (id != -1) {
		printf("Created Queue ID = %ld\n", id);
	}
	else {
		printf("Error creating message queue!\n");
	}

	return 0;
}