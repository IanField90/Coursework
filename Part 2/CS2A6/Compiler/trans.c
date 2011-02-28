#include <stdio.h>
#include "trans.h"
struct TransrealNumber evaluate(struct TransrealNumber *a, char opp, struct TransrealNumber *b){
	struct TransrealNumber retStruct;

	/* HANDLE NORMAL NUMBERS */
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
	/* HANDLE NULLITY */
	if (a->type == NULLITY || b->type == NULLITY) {
		retStruct.type = NULLITY;
		retStruct.value = 0;
		return retStruct;
	}
		
	/* HANDLE ONE (and only one) being INF or NEG_INF */
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
	/* HANDLE a NEG_INFINITY, b NEG_INFINITY */
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
	
	/* HANDLE a INFINITY, b INFINITY */
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

	/* HANDLE a INFINITY, b NEG_INFINITY */
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
	
	/* HANDLE a NEG_INFINITY, b INFINITY */
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

void display(struct TransrealNumber res){
	switch (res.type) {
		case NUMBER:
			printf("Result value is: %d\n", res.value);
			break;
		case INFINITY:
			printf("Return value is: INFINITY\n");
			break;
		case NEG_INFINITY:
			printf("Return value is: NEG_INFINITY\n");
			break;
		case NULLITY:
			printf("Return value is: NULLITY\n");
			break;
		default:
			break;
	}
}