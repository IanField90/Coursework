import sys
from pycsp import *

@process
def run(channel_arrives):
	while True:
		val = channel_arrives()
		sys.stdout.write("CarPark Arrive. Spaces left: %d \n" % (val))
