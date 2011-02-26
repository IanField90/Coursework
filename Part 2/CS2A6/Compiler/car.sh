#!/bin/sh

gcc lex.c -o lex
./lex test.c
rm lex

gcc trans.c parse.c -o generator
./generator
rm generator

cat program.c

echo "Code Generation complete"

gcc trans.c program.c -o prog
./prog
#rm prog