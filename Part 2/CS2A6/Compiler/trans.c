#include <stdio.h>

enum CLASSIFICATION { NUMBER, INFINITY, NEG_INFINITY, NULLITY };

struct TransrealNumber {
	enum CLASSIFICATION type;
	int value;
};

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
	
	// both nums, either nullity done
	
	//not checked: trans x num, tran / num
	// Mult : Signed infinity
	
	// 0 Mult : Nullity
	// 0 div
	
	
	/* HANDLE ONE (and only one) being INF or NEG_INF */
	if (a->type == NUMBER || b->type == NUMBER) {
		//TODO Mult : get Signed inf
		// Div : Keeps sign + type
		// if is 0 - zero , number result
		// if it's a
		if (a->type != NUMBER){
			//TODO switch operation
			retStruct.type = a->type;
			retStruct.value = 0;
			return retStruct;
		}
		// if it's b
		if (b->type != NUMBER){
			//TODO switch operation
			retStruct.type = b->type;
			retStruct.value = 0;
			return retStruct;
		}
	}
	
	/* HANDLE BOTH TRANS NUMBERS */

	/* HANDLE a INF, b NEG_INF */
	if ((a->type == INFINITY) && (b->type == NEG_INFINITY)) {
		retStruct.type = NULLITY;
		retStruct.value = 0;
		return retStruct;
	}
	
	/* HANDLE a NEG_INF, b INF */
	if ((a->type == NEG_INFINITY) && (b->type == NEG_INFINITY)) {
		retStruct.type = NULLITY;
		retStruct.value = 0;
		return retStruct;
	}
	
	/* HANDLE a NEG_INF, b NEG_INF */
	if ((a->type == NEG_INFINITY) && (b->type == NEG_INFINITY)) {
		retStruct.type = NEG_INFINITY;
		retStruct.value = 0;
		return retStruct;
	}
	
	/* HANDLE a INF, b INF */
	if ((a->type == INFINITY) && (b->type == INFINITY)){

		if (operation == '-') {
			retStruct.type = NULLITY;
			retStruct.value = 0;
		}
		else {
			retStruct.type = INFINITY;
			retStruct.value = 0;
		}
		return retStruct;
	}
	
}

int main(){
	struct TransrealNumber one, two, result;
	one.value = 0;
	one.type = NUMBER;
	two.value = 0;
	two.type = NUMBER;
	
	result = evaluate(&one, &two, '/');
	
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
