#include "dateUtil.h"

int main(){
	int d=0, m=0, y=0;
	int res=0;
/*	char mydate01[11] = {'0', '3', '/', '1', '1', '/', '2', '0', '0', '8', '\0'}; */
	char mydate1[11] = "03/11/2008";
	char mydate2[11] = "26/11/2008";
	
	printf("\n");
	printf("testing the conversion of a date representation from string to integers (d, m, y): \n");
	d = getDay(mydate1);
	if(d<0){
		printf("<main> Error (code %d) in converting the day: %s\n", d, mydate1);
		return -1;
	}
	m = getMonth(mydate1);
	if(m<0){
		printf("<main> Error (code %d) in converting the month: %s\n", m, mydate1);
		return -1;
	}
	y = getYear(mydate1);
	if(y<0){
		printf("<main> Error (code %d) in converting the year: %s\n", y, mydate1);
		return -1;
	}
	printf("%s ==> %d-%d-%d\n", mydate1, d, m, y);
	printf("\n");


	printf("testing dateCompare: \n");

	//MY CODE
	res = dateCompare(mydate1, mydate2);
	if(res == -9)
		printf("Error with dates \n");
	if(res == -1)
		printf("%s is before %s \n", mydate1, mydate2);
	if(res == 1)
		printf("%s is after %s \n", mydate1, mydate2);
	if(res == 0)
		printf("%s is the same as %s \n", mydate1, mydate2);


	system("PAUSE");
	return(1);
}
