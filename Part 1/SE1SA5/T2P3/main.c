#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

void generateTemperatures(float *firstEntry, int numDays, float startTemp);
float averageTemp(float *firstEntry, int startDay, int endDay);

int main(){
	int _startDay, _endDay, _numDays, i;
	float temperatureValues[SIZE], _startTemp, *ptr, _averageTemp;

	printf("Please input a start Temperature:\n");
	scanf("%f", &_startTemp);
	// Check range of provided start temperature
	if (_startTemp < -50 || _startTemp > 50){
		printf("Temperature out of expected range\n");
	}
	else{
		printf("Begining generation of temperatures...\n");
		ptr = &temperatureValues[0];
		generateTemperatures(ptr, SIZE, _startTemp);
		
		printf("Temperatures are:\n");
		for (i = 0; i<SIZE; i++){
			printf("%2.0f, ", temperatureValues[i]);
		}
		
		// Obtain values to pass to averageTemp();
		
		printf("\nPlease state the start day for average calculation:\n");
		scanf("%d", &_startDay);

		printf("Please state the end day for average calculation:\n");
		scanf("%d", &_endDay);

		_averageTemp = averageTemp(ptr, _startDay, _endDay);

		if(_averageTemp < 0){
			switch((int)_averageTemp){
				case -1:
					printf("Start day and end day must be > 0\n");
					break;
				case -2:
					printf("Start day must be before end day\n");
					break;
				case -3:
					printf("End day must not exceed 20\n");
					break;
				default:
					break;
			}
		}
		else
			printf("The average Temperature is: %2.1f\n", _averageTemp);
		}
	system("PAUSE");
	return 0;
	
}

void generateTemperatures(float *firstEntry, int numDays, float startTemp){
	int i;
	float newRandTemp;
	*firstEntry = startTemp;
	for (i = 0; i<numDays-1; i++){
		srand(firstEntry);
		firstEntry++;
		*firstEntry = rand() % 51;
	}
}

float averageTemp(float *firstEntry, int startDay, int endDay){
	float average, maxTemp, minTemp;
	int i;
	average = 0;
	if(startDay <= 0 || endDay <= 0)
		return -1;
	else if(endDay < startDay)
		return -2;
	else if(endDay > SIZE)
		return -3;

	firstEntry += (startDay - 1);
	maxTemp = *firstEntry;
	minTemp = *firstEntry;
	for(i=startDay-1; i < endDay; i++){
		average += *firstEntry;
		if (*firstEntry > maxTemp)
			maxTemp = *firstEntry;
		if (*firstEntry < minTemp)
			minTemp = *firstEntry;
		firstEntry++;
	}
	printf("The Maximum Temperature for the range is: %2.0f\n", maxTemp);
	printf("The Minimum Temperature for the range is: %2.0f\n", minTemp);
	average /= (endDay-startDay+1);

	return average;
}