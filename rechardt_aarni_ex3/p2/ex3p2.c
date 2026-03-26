#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// to run this code, use the following command in the terminal:
// gcc -o ex3p2 ex3p2.c -lm && ./ex3p2

#define N 15000
int a[N][N];
#define NPRINT 500
#define RUNS 100

void main() {
  int i,j, run;
  clock_t t1,t2;

  double times[RUNS];
  double sum = 0.0;
  double mean = 0.0;
  double variance = 0.0;
  double std_dev = 0.0;

for (run = 0; run < RUNS; run++) {
      
      /* Begin measurement */
      t1 = clock();
      for (i = 0; i < N; i++) 
        for (j = 0; j < N; j++) 
          a[i][j] = (i + j) / 2;
      t2 = clock();
      /* End measurement */
      
      times[run] = (t2 - t1) / (double)CLOCKS_PER_SEC;
      sum += times[run];
  }

  mean = sum / RUNS;

  for (run = 0; run < RUNS; run++) {
      variance += pow(times[run] - mean, 2);
  }
  variance /= RUNS;
  std_dev = sqrt(variance);


  for (i = 0; i < N; i += NPRINT) {
      for (j = 0; j < N; j += NPRINT) {
          printf("%d ", a[i][j]);
      }
  }
  printf("\n");
  
  printf("Average Time: %f seconds\n", mean);
  printf("Standard Deviation: %f seconds\n", std_dev);
}