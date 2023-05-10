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

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&nranks);

	if (nranks < 2 ) {
		printf("Need at least two MPI ranks. Quitting...\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
		exit(1);
	}

	if (myrank == 0) {
	  printf("MPI has started with %d tasks.\n", nranks);
	  for (i=0; i<NRA; i++)
		 for (j=0; j<NCA; j++)
			a[i][j]= i+j;
	  for (i=0; i<NCA; i++)
		 for (j=0; j<NCB; j++)
			b[i][j]= i*j;

	  /* Send matrix data to the worker tasks */
	  for (dest=?; dest<=nranks-1; dest++) {
		 rows = ?
		 printf("Sending %d rows to task %d offset=%d\n", ?, ?, ?);
		 ...
		 ...
		 ...
	  }

	  /* Receive results from worker tasks */
	  for (i=1; i<=nranks-1; i++) {
		 ...
		 ...
		 ...
		 printf("Received results from task %d\n", i);
	  }

	  printf ("Done.\n");
	}

   if (myrank > 0) {
		...
		...
		...
   }
   
   MPI_Finalize();
   return 0;
}
