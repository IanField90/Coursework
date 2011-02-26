#include "trans.h"
#include<stdio.h>
int main (){
struct TransrealNumber a;

struct TransrealNumber b;

struct TransrealNumber c;
a.type=NUMBER; a.value=4;
b.type=NUMBER; b.value=4;
c=evaluate(&a, '/', &b);
display(c);
return 0;
}
