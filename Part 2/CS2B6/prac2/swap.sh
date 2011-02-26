#!/bin/sh

if [ $# = 2 ]
	then
		if [ -f $1 ]
			then
				if [ -f $2 ]
					then
						#both exist, do copy
						cp $1 temp
						cp $2 $1
						cp temp $2
						rm temp
						echo "Files $1 and $2 have been swapped"
					else
						echo "$2 does not exist"
				fi
			else
				echo "$1 does not exist"
		fi
		
	else
		echo "Required parameters: file1 file2"
fi
