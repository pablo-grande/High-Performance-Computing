#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <memory.h>
#include <malloc.h>
#include <papi.h>

#define SIZE 1000

int main(int argc, char **argv) {

  float matrixa[SIZE][SIZE], matrixb[SIZE][SIZE], mresult[SIZE][SIZE];
  int i,j,k;
  int events[5] = {PAPI_TOT_INS, PAPI_L1_DCM, PAPI_L2_DCM, PAPI_L1_ICM, PAPI_L2_ICM}, ret;
  long long values[5];

  if (PAPI_num_counters() < 5) {
    fprintf(stderr, "No hardware counters here, or PAPI not supported.\n");
    exit(1);
  }

  if ((ret = PAPI_start_counters(events, 5)) != PAPI_OK) {
    fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(ret));
    exit(1);
  }

  /* Initialize the Matrix arrays */
  for ( i=0; i<SIZE*SIZE; i++ ){
    mresult[0][i] = 0.0;
    matrixa[0][i] = matrixb[0][i] = rand()*(float)1.1;
  }

  /* Matrix-Matrix multiply implementation 1 */
  for (i=0;i<SIZE;i++)
    for(j=0;j<SIZE;j++)
      for(k=0;k<SIZE;k++)
        mresult[i][j]=mresult[i][j] + matrixa[i][k]*matrixb[k][j];

  if ((ret = PAPI_read_counters(values, 5)) != PAPI_OK) {
    fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
    exit(1);
  }

  long long ins1 = values[0], l1_dcm1 = values[1], l2_dcm1 = values[2], l1_icm1 = values[3], l2_icm1 = values[4];

  if ((ret = PAPI_reset(events, 5)) != PAPI_OK) {
    fprintf(stderr, "PAPI failed to reset counters: %s\n", PAPI_strerror(ret));
    exit(1);
  }

  /* Matrix-Matrix multiply implementation 2 */
  for (k=0;k<SIZE;k++)
    for(j=0;j<SIZE;j++)
      for(i=0;i<SIZE;i++)
        mresult[i][j]=mresult[i][j] + matrixa[i][k]*matrixb[k][j];

  if ((ret = PAPI_read_counters(values, 5)) != PAPI_OK) {
    fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
    exit(1);
  }

  long long ins2 = values[0], l1_dcm2 = values[1], l2_dcm2 = values[2], l1_icm2 = values[3], l2_icm2 = values[4];

  printf("Implementation 1:\n");
  printf("Total instructions: %lld\n", ins1);
  printf("L1 data cache misses: %lld\n", l1_dcm1);
  printf("L2 data cache misses: %lld\n", l2_dcm1);
  printf("L1 instruction cache misses: %lld\n", l1_icm1);
  printf("L2 instruction cache misses: %lld\n", l2_icm2);

  exit(0);
}
