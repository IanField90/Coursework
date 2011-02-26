#include "dateUtil.h"

/*
   The function getDay converts an input date (string)
   into a numeric value (int) of the day.
   Input string format for a date: "dd/mm/yyyy"
   Returned code 
   -1: error, no input string
   -2: error: wrong format in input string
   >0: the day as integer
*/
int getDay(char date[]){
	char dd[3]; /* two digits for a day */
	int day;

	/* if incorrect input date, return error code -1 */
	if(date==NULL) return -1;
	if(strlen(date) != 10) return -1;

	/* if incorrect date format, return error code -2 
		index: 0 1 2 3 4 5 6 7 8 9
		 char: d d / m m / y y y y
	*/
	if((date[2] != DATE_FIELD_SEPARATOR) || (date[5] != DATE_FIELD_SEPARATOR)){
		printf("<dateConvert> Error: expected separator %c in the input string (%s).\n", 
				DATE_FIELD_SEPARATOR, date);
		return -2;
	}
	if ((!isdigit(date[0])) || (!isdigit(date[1]))) { /* digits of day */ 
		printf("<dateConvert> Error: a char in the input string (%s) is NOT a digit.\n", date);
		return -2;
	}

	dd[0] = date[0];
	dd[1] = date[1];
	dd[2] = '\0';
	day = atoi(dd);
	return(day); /* date successfully converted */
}

/*
   The function getMonth converts an input date (string)
   into a numeric value (int) of the month.
   Input string format for a date: "dd/mm/yyyy"
   Returned code 
   -1: error, no input string
   -2: error: wrong format in input string
   >0: the month as integer
*/
int getMonth(char date[]){
	char mm[3]; /* two digits for a month */
	int month;

	/* if incorrect input date, return error code -1 */
	if(date==NULL) return -1;
	if(strlen(date) != 10) return -1;

	/* if incorrect date format, return error code -2 
		index: 0 1 2 3 4 5 6 7 8 9
		 char: d d / m m / y y y y
	*/
	if((date[2] != DATE_FIELD_SEPARATOR) || (date[5] != DATE_FIELD_SEPARATOR)){
		printf("<dateConvert> Error: expected separator %c in the input string (%s).\n", 
				DATE_FIELD_SEPARATOR, date);
		return -2;
	}
	if((!isdigit(date[3])) || (!isdigit(date[4]))) { /* digits of month */ 
		printf("<dateConvert> Error: a char in the input string (%s) is NOT a digit.\n", date);
		return -2;
	}

	mm[0] = date[3];
	mm[1] = date[4];
	mm[2] = '\0';
	month = atoi(mm);
	return(month); /* date successfully converted */
}

/*
   The function getYear converts an input date (string)
   into a numeric value (int) of the year.
   Input string format for a date: "dd/mm/yyyy"
   Returned code 
   -1: error, no input string
   -2: error: wrong format in input string
   >0: the year as integer
*/
int getYear(char date[]){
	char yyyy[5]; /* four digits for a year */
	int year;

	/* if incorrect input date, return error code -1 */
	if(date==NULL) return -1;
	if(strlen(date) != 10) return -1;

	/* if incorrect date format, return error code -2 
		index: 0 1 2 3 4 5 6 7 8 9
		 char: d d / m m / y y y y
	*/
	if((date[2] != DATE_FIELD_SEPARATOR) || (date[5] != DATE_FIELD_SEPARATOR)){
		printf("<dateConvert> Error: expected separator %c in the input string (%s).\n", 
				DATE_FIELD_SEPARATOR, date);
		return -2;
	}
	if(    (!isdigit(date[6])) || (!isdigit(date[7])) /* digits #1 amd #2 of year */
		|| (!isdigit(date[8])) || (!isdigit(date[9])) ){ /* digits #3 and #4 of year */
		printf("<dateConvert> Error: a char in the input string (%s) is NOT a digit.\n", date);
		return -2;
	}

	yyyy[0] = date[6];
	yyyy[1] = date[7];
	yyyy[2] = date[8];
	yyyy[3] = date[9];
	yyyy[4] = '\0';
	year = atoi(yyyy);
	return(year); /* date successfully converted */
}

int dateCompare(char date1[], char date2[]){
	int result;
	struct date {
		int day;
		int month;
		int year;
	}dateOne, dateTwo;
	
	// Init Structure
	dateOne.day = getDay(date1);
	dateTwo.day = getDay(date2);
	dateOne.month = getMonth(date1);
	dateTwo.month = getMonth(date2);
	dateOne.year = getYear(date1);
	dateTwo.year = getYear(date2);

	
	if((dateOne.day < 0) || (dateTwo.day < 0))
		result = -9;
	if((dateOne.month < 0) || (dateTwo.month < 0))
		result = -9;
	if((dateOne.year < 0) || (dateTwo.year < 0))
		result = -9;

	if((dateOne.day < dateTwo.day) || (dateOne.month < dateTwo.month) || (dateOne.year < dateTwo.year))
		result = -1;
	if((dateOne.day > dateTwo.day) || (dateOne.month > dateTwo.month) || (dateOne.year > dateTwo.year))
		result = 1;
	if((dateOne.day == dateTwo.day) && (dateOne.month == dateTwo.month) && (dateOne.year == dateTwo.year))
		result = 0;

	return result;
}