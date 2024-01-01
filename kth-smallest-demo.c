#include "parallel.h"
#include <stdio.h>

num_t kth_smallest(num_t *arr, int n, int k);

int main(void)
{
  num_t arr[] = {4, 6, 3, 2, 4, 7, 5, 6};
  for(int i = 0; i < 8; ++i) {
    printf("%4g", kth_smallest(arr, 8, i + 1));
  }
  printf("\n");
  return 0;
}
