#!/bin/sh

#gcc lex.c -o lex
#./lex test.c
#rm lex

gcc trans.c -o trans
./trans
rm trans