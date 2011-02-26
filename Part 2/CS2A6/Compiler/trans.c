#include <stdio.h>
#include "trans.h"
struct TransrealNumber evaluate(struct TransrealNumber *a, struct TransrealNumber *b, char opp){
	struct TransrealNumber retStruct;

	/* HANDLE NORMAL NUMBERS (done) */
	if ((a->type == NUMBER) && (b->type == NUMBER)) {
		retStruct.type = NUMBER;
		switch (opp) {
			case '+':
				retStruct.value = a->value + b->value;
				break;
			case '-':
				retStruct.value = a->value - b->value;
				break;
			case '*':
				retStruct.value = a->value * b->value;
				break;
			case '/':
				// 0/0
				if (a->value == 0 && b->value == 0) {
					retStruct.value = 0;
					retStruct.type = NULLITY;
					return retStruct;
				}
				
				// +ve / 0
				if (a->value > 0 && b->value == 0) {
					retStruct.value = 0;
					retStruct.type = INFINITY;
					return retStruct;
				}
				
				// -ve / 0
				if (a->value < 0 && b->value == 0) {
					retStruct.value = 0;
					retStruct.type = NEG_INFINITY;
					return retStruct;
				}
				
				// any other
				if (b->value != 0) {
					retStruct.value = a->value / b->value;
				}

				break;
			default:
				break;
		}
		return retStruct;
	}
	
	// both nums done
	/* HANDLE NULLITY (done)*/
	if (a->type == NULLITY || b->type == NULLITY) {
		retStruct.type = NULLITY;
		retStruct.value = 0;
		return retStruct;
	}
	
	
	/* HANDLE ONE (and only one) being INF or NEG_INF */
	//TODO Handle negative numbers
	
	if (a->type == NUMBER || b->type == NUMBER) {
		if (a->type != NUMBER){
			// +/- inf * 0
			if (opp == '*' && b->value == 0) {
				retStruct.type = NULLITY;
			}
			else if (opp == '/' && b->value > 0) {
				retStruct.type = INFINITY;
			}
			else {
				retStruct.type = a->type;
			}
			retStruct.value = 0;
			return retStruct;
		}

		if (b->type != NUMBER){
			// 0 * +/- inf
			if (opp == '*' && a->value == 0) {
				retStruct.type = NULLITY;
			}// 0 / +/- inf
			else if (opp == '/' && a->value == 0){
				retStruct.type = NUMBER;
			}
			else {
				retStruct.type = b->type;
			}
			retStruct.value = 0;
			return retStruct;
		}
	}
	
	
	/* HANDLE BOTH TRANS NUMBERS */
	
	/* HANDLE a NEG_INFINITY, b NEG_INFINITY (done) */
	if ((a->type == NEG_INFINITY) && (b->type == NEG_INFINITY)) {
		
		switch (opp) {
			case '+':
				retStruct.type = NEG_INFINITY;
				break;
			case '-':
				retStruct.type = INFINITY;
				break;
			case '*':
				retStruct.type = INFINITY;
				break;
			case '/':
				retStruct.type = NULLITY;
				break;


			default:
				break;
		}
		
		retStruct.value = 0;
		return retStruct;
	}
	
	/* HANDLE a INFINITY, b INFINITY (done) */
	if ((a->type == INFINITY) && (b->type == INFINITY)){
		if (opp == '-' || opp == '/') {
			retStruct.type = NULLITY;
			retStruct.value = 0;
		}
		else {
			retStruct.type = INFINITY;
			retStruct.value = 0;
		}
		return retStruct;
	}

	/* HANDLE a INFINITY, b NEG_INFINITY (done)*/
	if ((a->type == INFINITY) && (b->type == NEG_INFINITY)) {
		switch (opp) {
			case '*':
				retStruct.type = NEG_INFINITY;
				break;
			case '+':
				retStruct.type = NULLITY;
				break;
			case '-':
				retStruct.type = INFINITY;
				break;
			case '/':
				retStruct.type = NULLITY;
				break;
		}
		
		retStruct.value = 0;
		return retStruct;
	}
	
	/* HANDLE a NEG_INFINITY, b INFINITY (done) */
	if ((a->type == NEG_INFINITY) && (b->type == INFINITY)) {
		if (opp == '+' || opp == '/') {
			retStruct.type = NULLITY;
		}
		else {
			retStruct.type = NEG_INFINITY;
		}
		retStruct.value = 0;
		return retStruct;
	}
	
}

/*
int main(){
	struct TransrealNumber one, two, result;
	one.value = -3;
	one.type = NUMBER;
	two.value = 0;
	two.type = NEG_INFINITY;
	
	result = evaluate(&one, &two, '*');
	
	switch (result.type) {
		case NUMBER:
			printf("Return type is: NUMBER\n");
			printf("Result value is: %d\n", result.value);
			break;
		case INFINITY:
			printf("Return type is: INFINITY\n");
			break;
		case NEG_INFINITY:
			printf("Return type is: NEG_INFINITY\n");
			break;
		case NULLITY:
			printf("Return type is: NULLITY\n");
			break;
		default:
			break;
	}
	

	return 0;
}
*/