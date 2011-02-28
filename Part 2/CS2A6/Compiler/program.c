#include "trans.h"
#include<stdio.h>
int main (){
struct TransrealNumber a,b,c;
a.type=NUMBER; a.value=1;
b.type=NUMBER; b.value=0;
c=evaluate(&a, '/', &b);
display(c);
a.type=NUMBER; a.value=-1;
c=evaluate(&a, '/', &b);
display(c);
a.type=NUMBER; a.value=0;
c=evaluate(&a, '/', &b);
display(c);
return 0;
}
