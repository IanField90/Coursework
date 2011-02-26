#ifndef STACK_H
#define STACK_H
#define SIZE 20

class Stack {
public:
	Stack ( );
	void push ( char );
	char pop ( );
	//char top( );
private:
	char chararray [ SIZE ];
	int tos;
};
#endif