#include <stdio.h>
#include <ctype.h>
#include <fcntl.h> /* File control - unsure if needed */
#include "lex.h"

FILE *inputFile;
int lexVal;
char lexText[256] = {0};

int main(int argc, char *argv[]){
	FILE *outputFile;
	outputFile = fopen("lexOutput.txt", "w+");
	char buffer[256] = {0};
	/* Perform lexical analysis */
	inputFile = fopen(argv[1], "r");
	int ch;
	printf("Entering %s\n\n", argv[1]);
	while ((ch = lex()) != EOF) {
		switch (ch) {
			case INT:
				fprintf(outputFile, "INT\n");
				break;
			case VOID:
				fprintf(outputFile, "VOID\n");
				break;
			case MAIN:
				fprintf(outputFile, "MAIN\n");
				break;

			case INTEGER:
				fprintf(outputFile, "INTEGER\t\t%d\n", lexVal);
				break;
			case IDENTIFIER:
				fprintf(outputFile, "IDENTIFIER\t\t%s\n", lexText);
				break;
			case UNKNOWN:
				fprintf(outputFile, "UNKNOWN\t\t%c %d\n", lexVal, lexVal);
				break;
				
			default:
				fprintf(outputFile, "%c\n", ch);
				break;
		}
	}
	fclose(inputFile);
	fclose(outputFile);
	/* Lexical analysis complete */
	
	return 0;
}

int reservedKWord(char name[]){
	if(strcmp(name, "int") == 0) return INT;
	if(strcmp(name, "void") == 0) return VOID;
	if(strcmp(name, "main") == 0) return MAIN;
	return IDENTIFIER;
}

int lex(){
	int i, ch;
	if ((ch = getc(inputFile)) == EOF) {
		return EOF;
	}
	
	switch (ch) {
		/* Skip whitespace */
		case ' ':
			return lex();
		case '\t':
			return lex();
		case '\n':
			return lex();
		
		/* handle comments or division */
		case '/':
			if ((ch = getc(inputFile)) == '*') {
				/* comment */
				do {
					ch = getc(inputFile);
					if(ch == '*'){
						//If it's the end of the comment
						if ((ch = getc(inputFile)) == '/') {
							return lex();
						}
					}
				} while (ch != '*');
			}
			else if(ch == '/') {
				// Double slash comment
				do {
					ch = getc(inputFile);
				} while (ch != '\n');
				return lex();
			}
			else {
				return DIVIDE;
			}
			
		/* Handle punctuation */
		case ',':
		case ';':
		case '.':
		case '(':
		case ')':
		case '[':
		case ']':
		case '{':
		case '}':
		case '<':
		case '>':
		case '+':
		case '-':
		case '*':
		case '=':
		case '#':
			lexVal = ch;
			return ch;
			
		/* Handle numbers */
		case '0': 
		case '1': 
		case '2': 
		case '3': 
		case '4': 
		case '5': 
		case '6': 
		case '7': 
		case '8': 
		case '9':
			lexVal = ch - '0';
			while (isdigit(ch = getc(inputFile)))
				lexVal = (lexVal*10) + ch - '0';
			
			fseek(inputFile, -1, SEEK_CUR);
			return INTEGER;
			
		/* Handle letters */
		case 'A':
		case 'B': 
		case 'C': 
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I': 
		case 'J': 
		case 'K': 
		case 'L': 
		case 'M': 
		case 'N': 
		case 'O': 
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z': 
		case 'a': 
		case 'b':
		case 'c':
		case 'd': 
		case 'e': 
		case 'f': 
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q': 
		case 'r': 
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			lexText[0] = ch;
			for (i = 1; isalnum(ch = getc(inputFile)); i++) {
				lexText[i] = ch;
			}
			fseek(inputFile, -1, SEEK_CUR); // On break ch is lost, file pointer decrement
			lexText[i++] = 0; /* zero terminated string */
			return reservedKWord(lexText);
			
		default:
			lexVal = ch;
			return UNKNOWN;
	}
}
