#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define NRA 1024                 /* number of rows in matrix A */
#define NCA 512                /* number of columns in matrix A */
#define NCB 512                  /* number of columns in matrix B */

int main (int argc, char *argv[]) {
	int	nranks,              /* number of tasks in partition */
		myrank,                /* a task identifier */
		rc;
	double	a[NRA][NCA],           /* matrix A to be multiplied */
		b[NCA][NCB],           /* matrix B to be multiplied */
		c[NRA][NCB];           /* result matrix C */
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nranks);

	if (nranks < 2) {
		printf("Need at least two MPI ranks. Quitting...\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
		exit(1);
	}

	int i, j;
	if (myrank == 0) {
		printf("MPI has started with %d tasks.\n", nranks);
		for (i = 0; i < NRA; i++)
			for (j = 0; j < NCA; j++)
				a[i][j] = i + j;
		for (i = 0; i < NCA; i++)
			for (j = 0; j < NCB; j++)
				b[i][j] = i * j;

		/* Send matrix data to the worker tasks */
		int rows, dest, offset;
		int chunk = NRA / (nranks - 1);
		for (dest = 1, offset = 0; dest <= nranks - 1; dest++) {
			rows = (dest != nranks - 1) ? chunk : (NRA - offset);
			printf("Sending %d rows to task %d offset=%d\n", rows, dest, offset);
			MPI_Send(&offset, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
			MPI_Send(&rows, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
			MPI_Send(&a[offset][0], rows * NCA, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
			MPI_Send(&b, NCA * NCB, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
			offset += rows;
		}

		/* Receive results from worker tasks */
		for (i = 1; i <= nranks - 1; i++) {
			MPI_Recv(&offset, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
			MPI_Recv(&rows, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
			MPI_Recv(&c[offset][0], rows * NCB, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &status);
			printf("Received results from task %d\n", i);
		}

		printf("Done.\n");
	}

	if (myrank > 0) {
		int offset, rows;
		MPI_Recv(&offset, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&rows, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&a, rows * NCA, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&b, NCA * NCB, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);

		/* Perform matrix multiplication */
		for (i = 0; i < rows; i++) {
			for (j = 0; j < NCB; j++) {
				c[i][j] = 0.0;
				for (int k = 0; k < NCA; k++) {
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}

		/* Send the results back to rank 0 */
		MPI_Send(&offset, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		MPI_Send(&rows, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		MPI_Send(&c, rows * NCB, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}

		
