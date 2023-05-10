#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <memory.h>
#include <malloc.h>
#include <omp.h>

#define SIZE 1000

int main(int argc, char **argv) {

  float matrixa[SIZE][SIZE], matrixb[SIZE][SIZE], mresult[SIZE][SIZE];
  int i,j,k;

  /* Initialize the Matrix arrays */
  #pragma omp parallel for collapse(2)
  for ( i=0; i<SIZE; i++ ){
    for ( j=0; j<SIZE; j++ ){
      mresult[i][j] = 0.0;
      matrixa[i][j] = matrixb[i][j] = rand()*(float)1.1;
    }
  }

  /* Matrix-Matrix multiply */
  #pragma omp parallel for private(k, i, j)
  for (k=0;k<SIZE;k++){
   for(j=0;j<SIZE;j++){
    for(i=0;i<SIZE;i++){
      mresult[i][j]=mresult[i][j] + matrixa[i][k]*matrixb[k][j];
    }
   }
  }

  exit(0);
}

