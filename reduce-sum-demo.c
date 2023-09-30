#include <stdio.h>

static int init_t(int p)
{
  for(;;) {
    int lowbit = p & -p;
    if(lowbit == p) return p >> 1;
    p += lowbit;
  }
}

int main(void)
{
  int A[5] = {0, 1, 2, 3, 4};
  int p = 5;
  for(int t = init_t(p); t; t >>= 1) {
    for(int k = 0; k < p; ++k) {
      A[k] += k + t < p ? A[k + t] : 0;
    }
  }
  printf("%d\n", A[0]);
  return 0;
}
