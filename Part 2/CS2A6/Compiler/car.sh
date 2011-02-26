#!/bin/sh

#gcc lex.c -o lex
#./lex test.c
#rm lex

gcc trans.c parse.c -o parser
./parser
rm parser

cat program.c