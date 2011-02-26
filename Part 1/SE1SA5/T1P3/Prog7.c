#include <stdio.h>
#define FREEZE -32
#define BOIL 212
#define LINE "-o-o-o-o-o-o-o-o-\n"
#define NAME "Ian\n"
int main ( )
{
	printf("in farenheit freezing occurs at: %d \n",
         FREEZE);
	printf("%s", LINE);
	printf("in farenheit boiling occurs at: %d \n",
         BOIL);
	printf("%s", LINE);
		/*Outputs NAME from the pre-processor*/
	printf("My name is %s\n", NAME);
	return 0;
}
