#!/bin/sh

if [ $# = 2 ]
	then
		gcc lex.c -o lex
		./lex $1
		rm lex

		gcc trans.c generator.c -o generator
		./generator
		rm generator

		echo "Code Generation complete"

		gcc trans.c program.c -o $2
		./prog
	else
		echo "Expected arguments: source desired_exeName"
fi