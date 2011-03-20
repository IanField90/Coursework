# roundRobinRun.sh

#PBS -S /bin/sh
#PBS -N MPI-Coursework
#PBS -l walltime=00:01:00
#PBS -l nodes=5:ppn=2
#PBS -q auto

cd $PBS_O_WORKDIR

BinName="./MPI-Coursework"

NN=`cat $PBS_NODEFILE | wc -l`

echo "Using $NN nodes:"
echo "Node in use:"
cat $PBS_NODEFILE

echo "Job output start"
mpirun -np $NN -machinefile $PBS_NODEFILE $BinName
echo "Job output end"