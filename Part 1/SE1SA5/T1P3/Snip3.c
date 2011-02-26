#include <stdio.h>

int main ()
{
int num =12;
printf ("num using   %%d is %d \n", num);
printf ("num using  %%1d is %1d \n", num);
printf ("num using  %%2d is %2d \n", num);
printf ("num using  %%3d is %3d \n", num);
printf ("num using  %%4d is %4d \n", num);
printf ("num using %%05d is %05d \n", num);
printf ("num using %%06d is %06d \n", num);
printf ("-num using %%4d is %4d \n", -num);
return 0;
}