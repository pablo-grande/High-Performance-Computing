#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 16000
//N=32000 takes less than 1 minute with 4 OpenMP threads
#define T 4

int main(int argc, char **argv) {

  long long A[T][N], B[T][N], avg[T];
  int i,j,k,l,sum,elems;

  srand(time(NULL));

  for(i=0; i<T; i++){
   for(j=0; j<N; j++){
    if(i<T/2){
     A[i][j]=N/2+rand()%(N/2);
    }
    else{
     A[i][j]=rand()%(N/8); 
    }
   }
  }

  for(i=0; i<T; i++){
   for(j=0; j<N; j++){
    sum=0;
    for(k=0; k<A[i][j]; k++){
     for(l=0; l<T; l++){
      if(l!=i){
       sum=(sum+A[l][j])%(N/8);
      }
     }
    }
    B[i][j]=(A[i][j]+sum)%N;
   }
  }

  for(i=0; i<2; i++){
   elems=N/2+rand()%(N/4);
   sum=0;
   for(j=0; j<N; j++){
     for(k=0; k<A[i][j]; k++){
       for(l=0; l<T; l++){
         sum=(sum+A[l][j])%(N/4);
       }
     }
   }
   avg[i]=sum/elems;
  }

  for(i=0; i<T; i++){
   for(j=0; j<N; j++){
     B[i][j]+=A[i][j]+avg[1];
   }
  }

  exit(0);
}
