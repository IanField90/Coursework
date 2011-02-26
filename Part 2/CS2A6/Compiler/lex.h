/* lex.h */
#define RETURN 'return'
#define COMMA ','
#define SEMICOLON ';'
#define DOT '.'

/* Brackets */
#define OPEN_PARENTHESIS '('
#define CLOSE_PARENTHESIS ')'
#define OPEN_CURLY_BRACE '{'
#define CLOSE_CURLY_BRACE '}'
#define OPEN_ANGLE '<'
#define CLOSE_ANGLE '>'

/* Operators */
#define PLUS '+'
#define MINUS '-'
#define TIMES '*'
#define DIVIDE '/'
#define ASSIGNMENT '='

/* Reserved keywords */
#define HASH '#'
#define VOID 256 
#define INT	257 
#define MAIN 258

/* Variables qualifiers */
#define IDENTIFIER 259
#define INTEGER 260

/* Catch master */
#define UNKNOWN -3

int reservedKWord(char name[]);
int lex();