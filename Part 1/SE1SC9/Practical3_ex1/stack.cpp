#include <iostream>
using std::cout;

#include "stack.h"

Stack::Stack( ) { tos = 0; }

void Stack::push ( char ch )
{
	if (tos >= SIZE ) {
		cout << "Stack is full"<< "\n";
		return;
	}
	chararray [tos] = ch;
	tos++;
}

char Stack::pop ( )
{
	if (tos <= 0) {
		cout << "Stack is empty"<< "\n";
		return 0;
	}
	tos--;
	return chararray[tos];
}

//char Stack::top()
//{
//
//}