//Alpha sting is moving point of width 5 for average and SD
#include <stdio.h>
#include <math.h>
#define SIZE 10
#define SCOPE 5

float square (float x)
{
	return x*x;
}

int main ()
{
	float fValues[SIZE] = {2.33, 32.9823, 2.723, 3.152, 6.273, 7.681, 6.73 , 9.423, 4.093, 1.94};
	float fAverages[SIZE-SCOPE], fStandardDeviations[SIZE-SCOPE];
	float fAverage, fStandardDeviation, fTotal = 0, fSDTotal = 0;
	int i, j;
	
	// Find average
	for(i=0; i<SIZE; i++)
	{
		// Find the sum of values
		fTotal += fValues[i];
	}
	fAverage = fTotal / SIZE;
	printf("The average for these numbers is: %3.4f\n", fAverage);
	
	// Find SD
	for(i = 0; i<SIZE; i++)
	{
		// Add to the xStandard deviation total the deviation
		fSDTotal += square((fValues[i] - fAverage));
	}
	fStandardDeviation = sqrt(fSDTotal / SIZE);
	
	printf("The standard deviation for these is: %3.4f\n", fStandardDeviation);
	
	printf("Calculating moving average and standard deviation\n");

	for(i=0; i<SIZE-SCOPE; i++)
	{
		fTotal = 0;
		for(j = i; j<(i+5); j++)
		{
			fTotal += fValues[j];
		}
		
		fAverage = (fTotal / SCOPE);
		fAverages[i] = fAverage;
		printf("Average for index %d to %d is %2.2f\n", i, j, fAverages[i]);
		
		for(j = i; j<(i+5); j++)
		{
			fSDTotal += square( fValues[j]- fAverage);
		}
		
		fStandardDeviation = sqrt(fSDTotal / SCOPE);
		fStandardDeviations[i] = fStandardDeviation;
		printf("Standard deviation for index %d to %d is %5.2f\n", i, j, fStandardDeviations[i]);
	}
	
	// Allow user to see result
	system("PAUSE");
	return 0;
}