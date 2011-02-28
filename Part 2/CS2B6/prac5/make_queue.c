#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(){
	long int id;
	struct msqid_ds *info;
	msgget(IPC_PRIVATE, IPC_CREAT);
	printf("Created Queue ID %ld\n", id);
	
	msgctl(id, IPC_STAT, info);
	printf("Opened Queue ID %ld\n", id);
	
	return 0;
}