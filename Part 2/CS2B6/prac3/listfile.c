#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	if (argc < 2) {
		printf("No file was provided.\n");
		return 1;
	}

	FILE *input;
	input = fopen(argv[1], "r");

	if (input != NULL) {
		int ch;
		
		while ((ch = getc(input)) != EOF) {
			printf("%c",ch);
		}
	}
	else {
		printf("File does not exist.\n");
	}

	return 0;
}
