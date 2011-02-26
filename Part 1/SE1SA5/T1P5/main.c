#include <stdio.h>
#define SENTINEL -999

int LeapCheck (year){
	if((year%400 == 0) || ((year%100 != 0 )&&(year%4 == 0)))
		return 1;
	else
		return 0;
}

int main ()
{
	const int YEAR = 1900;
	int nYears [10][3], nOperation, nStartYear, nEndYear, nYearDays, nYearEntry, i, j, n;
	// nYears [x][0] holds year, [x][1] holds 1 if leap 0 if not, [x][2]holds day of week
	// for 1st of jan that year

	// prompt user for the option of range or set of years
	printf("In this Leap year calculator 10 years is the maximum that are checked for\n");
	printf("Would you like to enter   1) A range   or    2) Set of years?\n");
	scanf("%d", &nOperation);
	
	// if the operation is range
	if(nOperation == 1){
		printf("\nPlease enter the start year: ");
		scanf("%d", &nStartYear);
		printf("\nPlease enter the end year: "); 
		scanf("%d", &nEndYear);
	
		//ensure that the year range is 10
		if ((nEndYear - nStartYear) > 9)
			printf("\nYear range is too great\n");
		else
		{
			// initialise day offset to 0
			n=0;
			// loop through the array index ( 0 - 9 ) and each year
			// within year range
			for(j = 0, i = nStartYear;   j < 10, i < nEndYear+1;   j++, i++)
			{
				// Fill array with years
				nYears[j][0] = i;
				// Check for leap years and store 1 if is leap year
				// store 0 if not leap year
				nYears[j][1] = LeapCheck(nYears[j][0]);
				
				// Calculate the difference between year and 1900
				n = (int) (nYears[j][0] - YEAR)/ 4;
				// Take one away from this if it is a leap year
				// as leap year effects the jan 1st after leap year
				if ((nYears[j][1] == 1))
					//reduce n until after leap year
					n--;
				// Check if the century value between the difference between leap year
				// added to 200 (first case from 1900) modulo 400 is 0
				// if it is 0 decrement n    this ensures centurys beyond 2000 will not
				// be seen as a leap year unless it is divisible by 400 exactly
				if (((  ( (nYears[j][0] - YEAR) - ((nYears[j][0] - YEAR)%100) ) +200 ) %400) == 0)
					n--;
				
				//Store the day of the week that 1/1 occurs on in the second collumn
				nYears[j][2] = (int)((nYears[j][0] - YEAR) + n)%7;

				// Check values in the second collum and print the
				//year and day that 1/1 falls on for the year
				switch(nYears[j][2])
				{
					case 0:
						printf("\n%d Monday\n", nYears[j][0]);
						break;
					case 1:
						printf("\n%d Tuesday\n", nYears[j][0]);
						break;
					case 2:
						printf("\n%d Wednesday\n", nYears[j][0]);
						break;
					case 3:
						printf("\n%d Thursday\n", nYears[j][0]);
						break;
					case 4:
						printf("\n%d Friday\n", nYears[j][0]);
						break;
					case 5:
						printf("\n%d Saturday\n", nYears[j][0]);
						break;
					case 6:
						printf("\n%d Sunday\n", nYears[j][0]);
						break;
					default:
						printf("\nERROR\n");
				}
			} 
			

		}
	}
	else if(nOperation == 2){
		printf("\nEnter -999 to end entry. 10 Entries Max\n");
		i = 0;
		nYearEntry = 0;
		// maximum inputs are 10
		for(i = 0; i < 9; i++)
		{
			scanf("%d", &nYearEntry);
			// check that entry was not SENTINEL
			if (nYearEntry == SENTINEL)
				break;
			else{
				// if not then store it, calculate if leap year or not
				nYears[i][0] = nYearEntry;
				nYears[i][1] = LeapCheck(nYears[i][0]);
				
				// Calculate the difference between year and 1900
				n = (int) (nYears[i][0] - YEAR)/ 4;
				// Take one away from this if it is a leap year
				// as leap year effects the jan 1st after leap year
				if (nYears[i][1] == 1)
					//reduce n until after leap year
					n--;
				// Check if the century value between the difference between leap year
				// added to 200 (first case from 1900) modulo 400 is 0
				// if it is 0 decrement n    this ensures centurys beyond 2000 will not
				// be seen as a leap year unless it is divisible by 400 exactly
				if (((  ( (nYears[i][0] - YEAR) - ((nYears[i][0] - YEAR)%100) ) +200 ) %400) == 0)
					n--;

				//Store the day of the week that 1/1 occurs on in the second collumn
				nYears[i][2] = (int)((nYears[i][0] - YEAR) + n)%7;

				// Check values in the second collum and print the
				//year and day that 1/1 falls on for the year
				switch(nYears[i][2])
				{
					case 0:
						printf("\n%d Monday\n", nYears[i][0]);
						break;
					case 1:
						printf("\n%d Tuesday\n", nYears[i][0]);
						break;
					case 2:
						printf("\n%d Wednesday\n", nYears[i][0]);
						break;
					case 3:
						printf("\n%d Thursday\n", nYears[i][0]);
						break;
					case 4:
						printf("\n%d Friday\n", nYears[i][0]);
						break;
					case 5:
						printf("\n%d Saturday\n", nYears[i][0]);
						break;
					case 6:
						printf("\n%d Sunday\n", nYears[i][0]);
						break;
					default:
						printf("\nERROR\n");
				}
			}
		}
	}
	else{
		//State that the user has incorrectly entered the operation
		printf("\nInvalid operation\n");
	}
	// allow user to see results
	system("PAUSE");
	return 0;
}
