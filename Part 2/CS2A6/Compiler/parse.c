#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trans.h"
#define SIZE 80

FILE *fp, *outputFile;

int main(int argc, char *argv[]){
	
	fp = fopen("lexOutput.txt", "r");
	outputFile = fopen("program.c", "w+");
	char line[SIZE];
	char *ptr;
	
	
	fprintf(outputFile, "#include \"trans.h\"\n");
	while (fgets(line, SIZE, fp) != NULL) {
		// if it's a single literal, print
		if (strlen(line) == 2) {
			if (line[0] == ';') {
				fprintf(outputFile, "%c\n", line[0]);
			}
			else {
				fprintf(outputFile, "%c", line[0]);
			}
		}
		else if(strcmp(line, "INT\n") == 0){
			fprintf(outputFile, "\nstruct TransrealNumber ");
		}
		else if ((ptr = strstr(line, "IDENTIFIER\t\t")) != NULL) {
			//It's an Identifier tag
			//Take away \n
			line[strlen(line)-1] = 0;
			fprintf(outputFile, "%s", (ptr + strlen("IDENTIFIER\t\t")));
			
		}
		else if ((ptr = strstr(line, "INTEGER\t\t")) != NULL) {
			//It's an integer so intitialise new type
			fprintf(outputFile, "{ NUMBER, %c }", *(ptr + strlen("INTEGER\t\t")));
		}
		else if ((ptr = strstr(line, "UNKNOWN\t\t")) != NULL){
			//remove \n
			line[strlen(line)-1] = 0;
			fprintf(outputFile, "%c", *(ptr + strlen("UNKNOWN\t\t")));
		}
		//Occur less often, so further on in checks to increase efficiency
		else if (strcmp(line, "VOID\n") == 0){
			fprintf(outputFile, "\nvoid ");
		}
		else if (strcmp(line, "MAIN\n") == 0){
			fprintf(outputFile, "main ");
		}
	}
	
	return 0;
}
