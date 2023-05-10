#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

double f(double x) {
    return (4.0 / (1.0 + x * x));
}

double fragment(double a, double b, long long unsigned int num_fragments, double h) {
    double est, x;
    long long unsigned int i;

    est = (f(a) + f(b)) / 2.0;
    for (i = 1; i <= num_fragments - 1; i++) {
        x = a + i * h;
        est += f(x);
    }
    est = est * h;

    return est;
}

int main(int argc, char** argv) {

    int rank, size;
    long long unsigned int n = 100000000000;
    double a = 0.0, b = 1.0, h = 0.0;
    double result = 0.0, total_result = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    h = (b - a) / n;

    long long unsigned int local_n = n / size;
    double local_a = a + rank * local_n * h;
    double local_b = local_a + local_n * h;
    double local_result = fragment(local_a, local_b, local_n, h);

    MPI_Reduce(&local_result, &total_result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result: %.20f\n", total_result);
    }

    MPI_Finalize();

    exit(0);
}
