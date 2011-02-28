#include <stdio.h>
void main(){
	int a, b, c;
	a = 1;
	b = 0;
	c = a / b;
	display(c);
	a = -1;
	c = a / b;
	display(c);
	a = 0;
	c = a / b;
	display(c);
}
