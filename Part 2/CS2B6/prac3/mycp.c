#include <stdio.h>

int main(int argc,char * argv[]){
	if (argc < 3) {
		printf("Expected usage: exe file1 file2\n");
		return 1;
	}
	
	FILE *input;
	FILE *output;
	input = fopen(argv[1], "r");
	output = fopen(argv[2], "r");
	int ch;
	if (input == NULL) {
		printf("Input file does not exist.\n");
	}
	else if (output != NULL){
		printf("Output file already exists.\n");
	}
	else {
		output = fopen(argv[2], "a");
		while ((ch = getc(input)) != EOF) {
			fputc(ch, output);
		}
		fclose(input);
		fclose(output);
	}
	return 0;
}
