#include "parallel.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void presum_thr(num_t *arr, int n, int nthr);

int main(void)
{
  int n = 10000;
  num_t *arr = (num_t *)malloc(n * sizeof(num_t));
  if(arr == NULL) abort();

  // Compare threading presum to real values.
  for(int i = 0; i < n; ++i) {
    arr[i] = i;
  }
  presum_thr(arr, n, 2);
  int t = 0;
  num_t d = 0;
  int di = 0;
  for(int i = 1; i < n; ++i) {
    t += i;
    num_t diff = fabs(arr[i] - t) / t;
    if(diff > d) d = diff, di = i;
  }
  printf("Maximum difference: [%d] %lg\n", di, (double)d);

  // Compare sequential presum to real values.
  t = 0;
  d = 0;
  di = 0;
  num_t nt = 0;
  for(int i = 1; i < n; ++i) {
    t += i;
    nt += i;
    num_t diff = fabs(nt - t) / t;
    if(diff > d) d = diff, di = i;
  }
  printf("Maximum difference: [%d] %lg\n", di, (double)d);

  free(arr);
  return 0;
}
