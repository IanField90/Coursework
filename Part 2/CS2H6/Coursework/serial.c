//  Created by Ian Field on 16/03/2011.
#include <stdio.h>
#include <stdlib.h>
//#include <mpi.h>

#define NUM_ROWS 4 //20k
#define NUM_COLUMNS 5 //5k
#define NUM_TIME_STEPS 1

//2D array of reservations, calloc inits to 0
float** makeBuff(int columns, int rows){
	int i;
	float** ret;
	ret = (float**) calloc(rows, sizeof(float*));
	if(ret == NULL){
		printf("Row alloc fault\n");
	}
	else{
		for(i = 0; i<rows; i++){
			ret[i] = (float*) calloc(columns, sizeof(float));
				if(ret[i] == NULL){
					printf("Column alloc fault\n");
				}
			}
		}
	return ret;
}

//Top left is 5.0
void setFixedTemp(float **grid){
	grid[0][0] = 5.0;
}

//Average temp of surrounding 'atoms'
float calcTemp(float o, float t, float l, float r, float b, int divisor){
	return (o + t + l + r + b) / (float)divisor;
}

int main(int argc, char **argv) {
	int divisor, i, j, k;
	float curVal, topVal, leftVal, rightVal, bottomVal;
	float **recBuff, **sendBuff;
	printf("about to allocate recBuff\n");
	recBuff = makeBuff(NUM_COLUMNS, NUM_ROWS);
	printf("about to allocate sendBuff\n");
	sendBuff = makeBuff(NUM_COLUMNS, NUM_ROWS);
	setFixedTemp(recBuff);
	
	//j column, k row
	for(i = 0; i < NUM_TIME_STEPS; i++){
		for(j = 0; j < NUM_COLUMNS; j++){
			for(k = 0; k < NUM_ROWS; k++){
				divisor = 5;
				if(k == 0){
					//top row
					divisor--;
					topVal = -1;
				}
				if(j == 0){
					//left column
					divisor--;
					leftVal = -1;
				}
				if(k == NUM_ROWS - 1){
					//bottom row
					divisor--;
					bottomVal = -1;
				}
				if(j == NUM_COLUMNS - 1){
					//right column
					divisor--;
					rightVal = -1;
				}
				//corners accounted for

	 
				//Do calculation
				if(topVal == -1){
					topVal = 0;
				}else{
					topVal = recBuff[k-1][j];
				}
				
				if(leftVal == -1){
					leftVal = 0;
				}else{
					leftVal = recBuff[k][j-1];
				}
				
				if(bottomVal == -1){
					bottomVal = 0;
				}else{
					bottomVal = recBuff[k+1][j];
				}
				
				if(rightVal == -1){
					rightVal = 0;
				}else{
					rightVal = recBuff[k][j+1];
				}
				
				curVal = recBuff[k][j];
				sendBuff[k][j] = calcTemp(curVal, topVal, leftVal, bottomVal, rightVal, divisor);
				
			}
			setFixedTemp(sendBuff);
			setFixedTemp(recBuff);
		}
	}

	
	// print results
	printf("Results!\n");
	
	for(j = 0; j < NUM_COLUMNS; j++){
		for(k = 0; k < NUM_ROWS; k++){
			printf("%1.2f ", sendBuff[k][j]);
		}
		printf("\n");
	}
	printf("End of Results!\n");
	
	if(sendBuff != NULL){
		for(i = 0; i < NUM_ROWS; i++){
			if(sendBuff[i] != NULL){
				free(sendBuff[i]);
			}
		}
		free(sendBuff);
	}
	if(recBuff != NULL){
		//Free memory again
		for(i = 0; i < NUM_ROWS; i++){
			if(recBuff[i] != NULL){
				free(recBuff[i]);
			}
		}
		free(recBuff);
	}
	return 0;
}
