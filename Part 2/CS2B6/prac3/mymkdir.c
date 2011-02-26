#include <stdio.h>
#include <stdlib.h>
#include <libc.h>


int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Expected argument: Directory name\n");
		return 1;
	}
	
	char command[256] = {0};
	
	if (opendir(argv[1]) == NULL) {
		/*Doesn't exist */
		sprintf(command, "mkdir '%s'", argv[1]);
		system(command);
	}
	else{
		printf("Directory already exists.\n");
	}
	
	return 0;
}