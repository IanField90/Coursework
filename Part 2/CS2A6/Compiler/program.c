#include "trans.h"
#include<stdio.h>
void main (){
struct TransrealNumber a;

struct TransrealNumber b;

struct TransrealNumber c;
a={ NUMBER, 3 };
b={ NUMBER, 4 };
c=a/b;
printf("%d\n",c);
}