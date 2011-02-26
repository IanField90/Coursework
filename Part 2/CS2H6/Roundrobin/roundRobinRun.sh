# roundRobinRun.sh

#PBS -S /bin/sh
#PBS -N MPI-RoundRobin
#PBS -l walltime=00:02:00
#PBS -l nodes=5:ppn=2
#PBS -q auto

cd $PBS_O_WORKDIR

BinName="./MPI-RoundRobin"

NN=`cat $PBS_NODEFILE | wc -l`

echo "Using $NN nodes:"
echo "Node in use:"
cat $PBS_NODEFILE

echo "Job output start"
mpirun -np $NN -machinefile $PBS_NODEFILE $BinName
echo "Job output end"