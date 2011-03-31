#!/bin/bash
mpicc -O3 main.c -o MPI-Coursework
qsub run.sh