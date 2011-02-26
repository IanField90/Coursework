#include <iostream>
#define SYMB_SIZE 12
using std::cout;

#include "stack.h"


// part b)
double Evaluate(char op, int num1, int num2);
// part c)
void EvalExpr(char symb[], char *op, Stack st);

int main ( )
{
	// part a)
	Stack s1, s2;
	s1.push ('l'); 	s2.push ('t');
	s1.push ('m'); 	s2.push ('u');  
	s1.push ('n');	s2.push ('v');

	for (int i=0; i<3; i++)
		cout << "Pop s1: " << s1. pop ( ) << "\n";
	for (int j=0; j<3; j++)
		cout << "Pop s2: " << s2. pop ( ) << "\n";
	// end part a)

	// part b)
	cout << "\nPerforming part b)\n" << "3 ^ 4 = " << Evaluate('*', 3, 4) << std::endl;
	

	// part c)
	char operands[5] = { '+', '-', '*', '/', '^' };
	Stack s3;

	char expression[] = {"521--314++*"};//'5', '2', '1', '-', '-', '3', '1', '4', '+', '+', '*', '\0'};
	EvalExpr(expression, operands, s3);


	system("PAUSE");
	return 0;
}

// part b)
double Evaluate(char op, int num1, int num2)
{
	double result = 0;
	// ideally switch but does not work with characters
	if (op == '+')
		result = num1 + num2;
	else if (op == '-')
		result = num1 - num2;
	else if (op == '*')
		result = num1 * num2;
	else if (op == '/')
		result = num1 / num2;
	else if (op == '^')
	{
		result = num1;
		// Start at one as assignment = ^1
		for(int i = 1; i < num2; i++){
			result *= num1;
		}
	}
	return result;
}

// part c)
void EvalExpr(char symb[], char op[], Stack st)
{

	int count = 0;
	for(int j = 0; j < 11; j++)
	{
		char* cur;
		cur = &symb[j];
			for(int i = 0; i < 5; i++)
			{
				if(op[i] == *cur)
				{
					st.push(Evaluate(op[i], st.pop(), st.pop()));
				}
			}
			count++;
			if (atoi(cur))
			{
				st.push(atoi(cur));
			}
	}
	cout << "Expression result is: " << st.pop() << '\n';
}


/*
Algorithm EvalExpr(Expr E)
	Stack eval;
	repeat {
		x = next_symbol(E)
		case x of :
			x is operand : Push(eval, x) break;
			x is operator : get correct number of operands off eval
							Compute the operations
							Put the result back on eval ;
							break;
			default : print (“answer is”, top(eval))
} until x is end of string
*/