#include <stdio.h>
#define SENTINEL -999

//Find day on any date

int LeapCheck (year){
	if((year%400 == 0) || ((year%100 != 0 )&&(year%4 == 0)))
		return 1;
	else
		return 0;
}

void PrintResult(dayCase, yearCase){
	switch(dayCase)
	{
		case 0:
			printf("\n%d Monday\n", yearCase);
			break;
		case 1:
			printf("\n%d Tuesday\n", yearCase);
			break;
		case 2:
			printf("\n%d Wednesday\n", yearCase);
			break;
		case 3:
			printf("\n%d Thursday\n", yearCase);
			break;
		case 4:
			printf("\n%d Friday\n", yearCase);
			break;
		case 5:
			printf("\n%d Saturday\n", yearCase);
			break;
		case 6:
			printf("\n%d Sunday\n", yearCase);
			break;
		default:
			printf("\nERROR\n");
	}
}


int main ()
{
	const int YEAR = 1900;
	int nYears [10][4], nOperation, nStartYear, nEndYear, nDateDays, nYearEntry, i, j, n, inputDay, inputMonth;
	int MonthInfo[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	//enum boolean { FALSE, TRUE } MyBool;
	int nMyBool;
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
				// if it is 0 decrement n    this ensures centuries beyond 2000 will not
				// be seen as a leap year unless it is divisible by 400 exactly
				// the first relevant occurance for this is 2100 so 200 is added before
				// the modulo found
				// MESSY
				if (((  ( (nYears[j][0] - YEAR) - ((nYears[j][0] - YEAR)%100) ) +200 ) %400) == 0)
					n--;
				
				//Store the day of the week that 1/1 occurs on in the second collumn
				nYears[j][2] = (int)((nYears[j][0] - YEAR) + n)%7;
				
				PrintResult(nYears[j][2], nYears[j][0]);
				// Check values in the second collum and print the
				//year and day that 1/1 falls on for the year
				
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
				/*
					1st of Jan for year now stored in array
					Day on date must now be calculated
					To do this the leap year column should be added
					to the value of MonthInfo[1];
					MonthInfo[] should then be summed
					Up to the month before the specified date (can be 0)
					Then the day from input added to it
					Then - 1 from this
					Then + nYears[i][2] to it (day of 1/1)
					The modulo 7 this value
					Switch and output this value as a day
				*/

				// Verify month is valid
				// TODO: Put in function
				nMyBool = 0;
				printf("Please input the month number: ");
				scanf("%d", &inputMonth);
				while(nMyBool == 0){
					if((inputMonth <= 12) && (inputMonth > 0)){
						nMyBool = 1;
					}
					else {
						printf("Invalid please input the month number: ");
						scanf("%d", &inputMonth);
					}
				}
				inputMonth--;
				
				// If leap year give feb 29 days
				if (nYears[i][1] == 1)
					MonthInfo[1] = 29;
				else
					MonthInfo[1] = 28;

				// Verify day is valid
				// TODO: Put in function
				nMyBool = 0;
				printf("Please input the day number: ");
				scanf("%d", &inputDay);
				while(nMyBool == 0){
					if((inputDay <= MonthInfo[inputMonth]) && (0 < inputDay)){
						nMyBool = 1;
					}
					else {
						printf("Invalid please input the day number: ");
						scanf("%d", &inputDay);
					}
				}
				
				// Find number of days from Jan 1
				nDateDays = 0;
				for (j = 0; j < inputMonth; j++){
					nDateDays += MonthInfo[j];
				}
				nDateDays += inputDay;
				nDateDays--;
				//nDateDays += nYears[i][2];

				// Find day of the week
				nYears[i][3] = ((nDateDays + nYears[i][2]) % 7);
				//nYears[i][3] += nYears[i][2];
				// Check values in the second collum and print the
				//year and day that 1/1 falls on for the year
				PrintResult(nYears[i][3], nYears[i][0]);
				printf("Next year: ");
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