#!/bin/sh

myDate=$(date "+%Y%m%d%H%M%S")

if [ -d mybackups ]
	then
		for i in *.sh
			do
				cp $i "mybackups/$i$myDate"
			done
	else
		mkdir mybackups
		for i in *.sh
			do
				cp $i "mybackups/$i$myDate"
			done
fi