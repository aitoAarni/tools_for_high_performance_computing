
A simple example to demonstrate parallel MPI runs
=================================================

A.Kuronen, antti.kuronen@helsinki.fi, 24.3.2026

If you are using your own computer with all necessary packages installed
------------------------------------------------------------------------
```
mpicc -o mpiexample mpiexample.c
```
or
```
mpif90 -o mpiexample mpiexample.f90
```
To run the code use this command:
```
mpirun -np NP ./mpiexample
```
where `NP`is the number of CPU cores and processes started.

If you are using Puhti
----------------------

You must have the student project on CSC in order to use Puhti.

You must load the needed tools:
```
module load gcc openmpi
mpicc -o mpiexample mpiexample.c
```
or
```
module load gcc openmpi
mpif90 -o mpiexample mpiexample.f90
```

To run the program, send the batch job for execution (**never run it on the frontend**) using the script `submit`:
```
sbatch submit
```
You can check out the progress of your job:
```
squeue
```
or
```
squeue -u <username>
```
Ouput of the run goes to file 'out_jobid', where `jobid` is your job identifier, shown also as the first column of `squeue` output.
