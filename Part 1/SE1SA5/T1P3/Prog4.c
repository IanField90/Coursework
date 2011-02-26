#include <stdio.h>

int num; /* define num */

int main ( )
{
	extern int num; /* explicitly declare num is needed*/
	num = 5; /*use num*/
	/* more code */
	printf ("The value of num is now %d\n", num);
	return 0;
}
/* other function that can use num
   also declares:
   extern int num;
   access the same num - values retained */
