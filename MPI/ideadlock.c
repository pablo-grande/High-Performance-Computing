#include <mpi.h>
#include <stdio.h>

#define SIZE 100000

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Rank %d is reported\n", rank);
    if (rank == 0) printf("Rank size: %d\n", size);
        int v1[SIZE];
        int v2[SIZE];
    // request input and status output for MPI_Wait function
    MPI_Request request;
    MPI_Status status;
    if (rank == 0) {
        int partner = 1;
        MPI_Isend(v1, SIZE, MPI_INT, partner, 100, MPI_COMM_WORLD, &request);
        printf("Rank %d sends to %d\n", rank, partner);
        MPI_Irecv(v2, SIZE, MPI_INT, partner, 100, MPI_COMM_WORLD, &request);
        printf("Rank %d receives from %d\n", rank, partner);
        MPI_Wait(&request, &status);
    }
    else if (rank == 1) {
        int partner = 0;
        MPI_Isend(v1, SIZE, MPI_INT, partner, 100, MPI_COMM_WORLD, &request);
        printf("Rank %d sends to %d\n", rank, partner);
        MPI_Irecv(v2, SIZE, MPI_INT, partner, 100, MPI_COMM_WORLD, &request);
        printf("Rank %d receives from %d\n", rank, partner);
        MPI_Wait(&request, &status);
    }

    MPI_Finalize();
}
