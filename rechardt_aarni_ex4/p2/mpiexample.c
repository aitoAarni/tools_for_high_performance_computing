#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc,char *argv[])
{
  const int tag=50;
  int id, ntasks, source_id, rc, pnlen;
  MPI_Status status;
  char pname[MPI_MAX_PROCESSOR_NAME];

  rc=MPI_Init(&argc,&argv);
  if (rc != MPI_SUCCESS) {
    printf("MPI initialization failed\n");
    exit(1);
  }
  rc=MPI_Comm_size(MPI_COMM_WORLD,&ntasks);
  rc=MPI_Comm_rank(MPI_COMM_WORLD,&id);
  rc=MPI_Get_processor_name(pname,&pnlen);
  int N = atoi(argv[1]);
  int counter = 0;

  if (id == 0) {
  for (int i = 0; i < N; ++i) {
    if (i % 2 == 0) {
      
      rc=MPI_Send(&counter,1,MPI_INT, 1,tag, MPI_COMM_WORLD);
    } else {
      rc=MPI_Recv(&counter,1,MPI_INT,MPI_ANY_SOURCE,tag, MPI_COMM_WORLD,&status);
      counter++;
    }
  }
  } else {

  for (int i = 0; i < N; ++i) {
    if (i % 2 == 0) {
      rc=MPI_Recv(&counter,1,MPI_INT,MPI_ANY_SOURCE,tag, MPI_COMM_WORLD,&status);
      counter++;
      source_id=status.MPI_SOURCE;
    } else {
      rc=MPI_Send(&counter,1, MPI_INT, 0,tag, MPI_COMM_WORLD);
    }
    }
  }
  if (N % 2 == id) {
    printf("Final counter value at rank %d: %d\n", id, counter);
  }
  rc=MPI_Finalize();
  exit(0);
}
