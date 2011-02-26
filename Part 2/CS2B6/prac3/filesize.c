#include <stdio.h>
#include <sys/stat.h>

int main(int argc,char * argv[]){	
	if (argc < 2) {
		printf("No file supplied.\n");
	}
	else {
		struct stat dir_stat;
	
		if (stat(argv[1], &dir_stat) == 0) {
			printf("Filesize is: %d bytes\n", (int)dir_stat.st_size);
		}
	}
	return 0;
}
