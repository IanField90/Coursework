import sys
from pycsp import *
from carpark import carpark
from eticket import eticket
from booking import booking

Parallel(
	carpark.run(),
	booking.run(),
	eticket.run()
)