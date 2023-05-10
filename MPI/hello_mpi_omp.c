#include <omp.h>
#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int rank, numprocs;
	char hostname[256];
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	gethostname(hostname,255);
	
	int nthreads, tid;
	#pragma omp parallel private(nthreads, tid)
	{
		tid = omp_get_thread_num();
		printf("Hello world! I am thread %d/%d of process %d/%d MPI on host %s\n", tid, omp_get_num_threads()-1, rank, numprocs-1, hostname);
	}
	MPI_Finalize();
	return 0;
}