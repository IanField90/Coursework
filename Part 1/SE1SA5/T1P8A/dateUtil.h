#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define DATE_FIELD_SEPARATOR '/'
int getDay(char date[]);
int getMonth(char date[]);
int getYear(char date[]);
int dateCompare(char date1[], char date2[]);