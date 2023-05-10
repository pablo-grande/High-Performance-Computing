#include "mpi.h"
#include <stdio.h>
#include <unistd.h>

void func1(int rank, char* hostname) {
	printf("Even rank %d on host %s is running function %s\n" , rank, hostname, __func__);
}
void func2(int rank, char* hostname) {
	printf("Odd rank %d on host %s is running function %s\n" , rank, hostname, __func__);
}

int main(int argc, char **argv)
{
  int rank, numprocs;
  char hostname[256];

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  gethostname(hostname,255);

  printf("Hello world! I am process number %d of %d MPI processes on host %s\n", rank, numprocs, hostname);

  MPI_Finalize();
  return 0;
}