#include <stdio.h>

int main ()
{
	//Declaration of variables and assignment of conversion rate
	//to '1.1045'
	int nOperation;
	float fInput, fResult, fConversionRate = 1.1045;

	//prompt the user for the operation that they wish to perform
	printf("Please input the operation that you wish to perform\n");
	printf("1. GBP to Euro      2. Euro to GBP:\n");
	//get the operation they wish to perform
	scanf("%d", &nOperation);
	//prompt user for the value that the conversion should be
	//performed on
	printf("\nPlease input the value you wish to convert from:\n");
	//get the value to be converted from
	scanf("%f", &fInput);

	//check if the operation to perform is GBP to Euro
	if (nOperation == 1)
	{
		//if it is then calculate the conversion result
		fResult = fInput * fConversionRate;
		//print the result to the console
		printf("\nThe conversion result is: %8.2f Euros\n", fResult);
	}
	//otherwise check if the operation to perform is
	//Euro to GBP
	else if (nOperation == 2)
	{	
		//if it is then calculate the conversion result
		fResult = fInput / fConversionRate;
		//print the result to the console
		printf("\nThe conversion result is: %8.2f GBP\n", fResult);
	}	

	//return 0 to the debugger if the program has executed correctly
	return 0;
}
