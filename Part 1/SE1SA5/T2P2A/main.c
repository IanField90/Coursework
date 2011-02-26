#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 80

int mySearch(char *ptr, char *word){
	int _count = 0;
	ptr = strstr(ptr, word);
		if (ptr){
			_count++;
			// Move pointer on from first instance
			ptr += 1;
			_count += mySearch(ptr, word);
		}	
	return _count;
}

int main (){
	// SIZE+1 to allow for Zero termination
	char mainArray[100][SIZE + 1], arrayRow[SIZE + 1], searchWord[20], *myPtr;
	int i, j;
	// Clear all data in the array so no random string is analised
	for(i=0, j=0; i<100, j<SIZE + 1; i++, j++){
		mainArray[i][j] = '\0';
	}
	printf("Please type some words so I can count how many times one you specify appears in it\n");
	i=0;
	while(fgets(&arrayRow, SIZE+1, stdin)){
		if(arrayRow[0]=='\n')
			break;
		myPtr = &mainArray[i];
		strcpy(myPtr, &arrayRow);		
		i++;
	}

	printf("First row is %s\n", mainArray[0]);
	printf("\n\nPlease enter a word to search for: \n");
	//fgets(searchWord, 20, stdin);
	scanf("%s", &searchWord);
	i=0;
	// Have a look for the word
	for(j=0; j<100; j++){
			// Row by row
		if (mainArray[j][0] != '\0'){
			i += mySearch(&mainArray[j][0], &searchWord);
		}
		else
			break;
	}
	if (i > 0)
		printf("The word appears %d times.\n", i);
	if(i == 0)
		printf("Word not found\n");

	system("PAUSE");
	return 0;
}