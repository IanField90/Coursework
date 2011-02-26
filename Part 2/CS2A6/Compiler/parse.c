#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trans.h"
#define SIZE 80

FILE *fp, *outputFile;
char line[SIZE];
char *ptr;
char lastID;

void parse();

int main(int argc, char *argv[]){
	
	fp = fopen("lexOutput.txt", "r");
	outputFile = fopen("program.c", "w+");
	
	fprintf(outputFile, "#include \"trans.h\"\n");
	
	
	while (fgets(line, SIZE, fp) != NULL) {
		parse();
	}
	
	fseek(outputFile, -1, SEEK_CUR);
	fprintf(outputFile, "return 0;\n}\n");
	return 0;
}

void parse(){
	int i = 0;
	char op[3] = {0};
	
	// if it's a single literal, print
	if (strlen(line) == 2) {
		if (line[0] == ';') {
			fprintf(outputFile, "%c\n", line[0]);
		}
		else if(line[0] == '=') {
			fprintf(outputFile, "%c", line[0]);
			//Create evaluation function on RHS
			if ((fgets(line, SIZE, fp) != NULL) && ((ptr = strstr(line, "IDENTIFIER\t\t")) != NULL)) {
				op[i] = *(ptr + strlen("IDENTIFIER\t\t"));
				i++;
				if (fgets(line, SIZE, fp) != NULL && strlen(line) == 2) {
					op[i] = line[0];
					i++;
					if (fgets(line, SIZE,fp) != NULL &&
						((ptr = strstr(line, "IDENTIFIER\t\t")) != NULL)) {
						op[i] = *(ptr + strlen("IDENTIFIER\t\t"));
						fprintf(outputFile, "evaluate(&%c, '%c', &%c)", op[0], op[1], op[2]);
					}
					else {
						parse();
					}

				}
				else {
					parse();
				}
			}
			else {
				parse();
			}

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
		//if(strlen(ptr + strlen("IDENTIFIER\t\t")) == 2)
			lastID = *(ptr + strlen("IDENTIFIER\t\t"));
		
	}
	else if ((ptr = strstr(line, "INTEGER\t\t")) != NULL) {
		//It's an integer so intitialise new type
		//TODO SORT OUT
		fseek(outputFile, -1, SEEK_CUR);
		fprintf(outputFile, ".type=NUMBER; %c.value=%c", lastID ,*(ptr + strlen("INTEGER\t\t")));
	}
	else if ((ptr = strstr(line, "UNKNOWN\t\t")) != NULL){
		//remove \n
		line[strlen(line)-1] = 0;
		fprintf(outputFile, "%c", *(ptr + strlen("UNKNOWN\t\t")));
	}
	//Occur less often, so further on in checks to increase efficiency
	else if (strcmp(line, "VOID\n") == 0){
		//only should occur before main
		//print int return type to remove C compiler warning
		fprintf(outputFile, "\nint ");
	}
	else if (strcmp(line, "MAIN\n") == 0){
		fprintf(outputFile, "main ");
	}
}