#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
  const int tag = 50;
  int id, ntasks, rc, i;
  MPI_Status status;
  int pnlen;
  char pname[MPI_MAX_PROCESSOR_NAME];

  rc = MPI_Init(&argc, &argv);
  if (rc != MPI_SUCCESS) {
    printf("MPI initialization failed\n");
    exit(1);
  }
  rc = MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
  rc = MPI_Comm_rank(MPI_COMM_WORLD, &id);
  rc = MPI_Get_processor_name(pname, &pnlen);

  // Requirement: Exactly two processes
  if (ntasks != 2) {
    if (id == 0) {
      printf("Error: This program requires exactly 2 processes.\n");
    }
    MPI_Finalize();
    exit(1);
  }

  // Requirement: Read N from command line arguments
  if (argc != 2) {
    if (id == 0) {
      printf("Usage: mpirun -np 2 ./pingpong <N>\n");
    }
    MPI_Finalize();
    exit(1);
  }

  int N = atoi(argv[1]);
  int counter = 0; // Initialize integer to zero

  // Ping-pong communication N times
  for (i = 0; i < N; i++) {
    if (i % 2 == 0) {
      // Even turn: Rank 0 sends, Rank 1 receives
      if (id == 0) {
        rc = MPI_Send(&counter, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
      } else if (id == 1) {
        rc = MPI_Recv(&counter, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        counter++; // Increment each time it is received
      }
    } else {
      // Odd turn: Rank 1 sends, Rank 0 receives
      if (id == 1) {
        rc = MPI_Send(&counter, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
      } else if (id == 0) {
        rc = MPI_Recv(&counter, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
        counter++; // Increment each time it is received
      }
    }
  }

  // Requirement: In the end, the receiving process prints the value.
  // If N is odd, Rank 1 catches the last pass. If N is even, Rank 0 catches it.
  int final_receiver = (N % 2 != 0) ? 1 : 0;
  
  if (id == final_receiver) {
    printf("Process %d on host %s received the final value: %d\n", id, pname, counter);
  }

  rc = MPI_Finalize();
  exit(0);
}