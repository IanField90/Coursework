#include <stdio.h>

int main ()
{
	//Declaration of variables and assignment of conversion rate
	//to GBP
	int nOperation;
	float fInput, fGBPResult, fEuroResult, fAusDollarResult, fYenResult, fConversionRate[3] = {1.1045, 2.33, 1000.2};

	//prompt the user for the operation that they wish to perform
	printf("Please input the type that you wish to enter\n");
	printf("1. GBP   2. Euro  3. Aus Dollar 4. Yen\n");
	//get the operation they wish to perform
	scanf("%d", &nOperation);
	//prompt user for the value that the conversion should be
	//performed on
	printf("\nPlease input the value you wish to convert from:\n");
	//get the value to be converted from
	scanf("%f", &fInput);

	//check if the operation to perform is GBP
	switch(nOperation)
	{
	case 1:
		{
		//if it is then calculate the conversion result
			fEuroResult = fInput * fConversionRate[0];
			fAusDollarResult = fInput * fConversionRate[1];
			fYenResult = fInput * fConversionRate[2];
			//print the result to the console
			printf("\nThe conversion result is: \n");
			printf("%8.2f Euros\n", fEuroResult);
			printf("%8.2f Aus Dollars\n", fAusDollarResult);
			printf("%8.2f Yen\n", fYenResult);
		} break;
		//otherwise check if the operation to perform is
		//Euro to GBP
	case 2:
		{	
			fGBPResult = fInput / fConversionRate[0];
			fAusDollarResult = fConversionRate[1] * fGBPResult;
			fYenResult = fInput * fGBPResult;

			//print result to console
			printf("\nThe conversion result is: \n");
			printf("%8.2f GBP\n", fGBPResult);
			printf("%8.2f Aus Dollars\n", fAusDollarResult);
			printf("%8.2f Yen\n", fYenResult);
		}
		break;
	
	case 3:
		{
			fGBPResult = fInput / fConversionRate[1];
			fYenResult = fConversionRate[2] * fGBPResult;
			fEuroResult = fConversionRate[0] * fGBPResult;

			printf("\nThe conversion result is: \n");
			printf("%8.2f GBP\n", fGBPResult);
			printf("%8.2f Yen\n", fYenResult);
			printf("%8.2f Euros\n", fEuroResult);
		}
		break;

	case 4:
		{
			fGBPResult = fInput / fConversionRate[2];
			fAusDollarResult = fGBPResult * fConversionRate[1];
			fEuroResult = fGBPResult * fConversionRate[0];
			printf("\nThe conversion result is: \n");
			printf("%8.2f GBP\n", fGBPResult);
			printf("%8.2f Aus Dollars\n", fAusDollarResult);
			printf("%8.2f Euros\n", fEuroResult);

		}
		break;

	default:
		printf("Incorrect entry\n");
	}

	//return 0 to the debugger if the program has executed correctly
	return 0;
}
