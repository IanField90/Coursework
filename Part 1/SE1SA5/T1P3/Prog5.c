#include <stdio.h>

int main ( )
{
	int i = 3;
	char j = '1';
	char myChar = 'B';
	int myInt = 2;
	printf("int i is:%d \n" , i);
	printf("char j is: %c \n", j);
	i = (int) j; /* cast j as an int */
	myInt = (int) myChar; /* cast myChar as int */
	printf("int i is:%d \n" , i);
	printf("char j is: %c \n", j);
	printf("char myChar is casted as %d \n", myInt);
	return 0;
}
