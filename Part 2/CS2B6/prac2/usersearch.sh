#!/bin/sh
if [ $# -gt 2 ]
	then
		echo "Too many arguments. Expected arguement: user to search for "
	else
		output=$(who | grep "^$1 " | wc -l)
		if [ $output -gt 0 ]
			then
				echo "User $1 is logged in."
			else
				echo "User $1 is not logged in."
		fi
fi
