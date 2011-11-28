import sys
from pycsp import *

MAX_SPACES = 50

# @choice
# def arrives():
# 	pass
# 	
# @choice
# def departs():
# 	pass

@process
def run(channel_arrives, channel_departs):
	spaces = MAX_SPACES
	while True:
		# TODO choices here instead, move if statments into functions
		if spaces > 0:
			spaces -= 1
			channel_arrives(spaces)
		
		if spaces < MAX_SPACES:
			spaces += 1
			channel_departs(spaces)