#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 12

int main(){
	char myString[SIZE], myString1[SIZE], myString2[SIZE], myString3[SIZE];
	char *myPtr;

	// Pseudocode 1
	printf("Please input the first string: \n");
	fgets(&myString, SIZE, stdin);
	if((myPtr = strchr(myString, '\n')) != NULL)
		*myPtr = '\0';

	strcpy(&myString1, &myString);
	printf("Please input the Second string: \n");
	fgets(&myString, SIZE, stdin);
	if((myPtr = strchr(myString, '\n')) != NULL)
		*myPtr = '\0';
	strcpy(&myString2, &myString);
	printf("\n#1 strcpy done.\n\n");
	
	// Pseudocode 2
	if ((strlen(myString1) + strlen(myString2) + 3) < SIZE){
		printf("The first string value is:\n %s \n", myString1);
		strcat(&myString1, " & ");
		strcat(&myString1, &myString2);
		printf("This is the first string & string2:\n %s \n", myString1);
	}
	printf("\n#2 strcat done.\n\n");

	// Pseudocode 3
	myPtr = strchr(&myString1, '&');
	myPtr += 2;
	while (*myPtr != '\0'){
		printf("%c", *myPtr);
		myPtr++;
	}
	printf("\n#3 strchr done.\n\n");

	// Pseudocode 4
	myPtr = strstr(&myString1, &myString2);
	strcpy(&myString3, myPtr);
	printf("\n#4 strstr done.");

	// Pseudocode 5
	if(strcmp(&myString2, &myString3) == 0)
		printf("\n the strings are identical\n");
	else
		printf("\n the strings are different - something went wrong\n");

	printf("\n#5 strcmp done.\n\n");


	// Pseudocode 6
	printf("Practical on String completed.\n");

	system("PAUSE");
	return 0;
}