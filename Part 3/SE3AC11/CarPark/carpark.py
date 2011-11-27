import sys

from pycsp import *
import carpark_arrival
import carpark_departs
import carpark_control

@process
def run():
	arrives = Channel()
	departs = Channel()

	Parallel(
		carpark_arrival.run(+arrives),
		carpark_control.run(-arrives, -departs),
		carpark_departs.run(+departs)
	)