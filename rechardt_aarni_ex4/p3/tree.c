#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int id, ntasks, rc;
    MPI_Status status;
    const int tag = 50;

    rc = MPI_Init(&argc, &argv);
    if (rc != MPI_SUCCESS) {
        printf("MPI initialization failed\n");
        exit(1);
    }

    rc = MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    rc = MPI_Comm_rank(MPI_COMM_WORLD, &id);


    int local_sum = id; 
    int received_val = 0;

    for (int step = 1; step < ntasks; step *= 2) {
        
        if (id % (2 * step) == 0) {
            int source_id = id + step;
            rc = MPI_Recv(&received_val, 1, MPI_INT, source_id, tag, MPI_COMM_WORLD, &status);
            local_sum += received_val;
        } 
        else if (id % (2 * step) == step) {
            int dest_id = id - step;
            rc = MPI_Send(&local_sum, 1, MPI_INT, dest_id, tag, MPI_COMM_WORLD);
            break; 
        }
    }

    if (id == 0) {
        printf("The total sum of all process IDs (0 to %d) is: %d\n", ntasks - 1, local_sum);
    }

    rc = MPI_Finalize();
    return 0;
}