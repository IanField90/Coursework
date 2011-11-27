import sys
from pycsp import *

@process
def run(channel_departs):
	while True:
		val = channel_departs()
		sys.stdout.write("CarPark Departs. Spaces left: %d\n" % (val))
