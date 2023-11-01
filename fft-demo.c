#undef __cplusplus
#include "parallel.h"
#include <complex.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void fft(cmp_t *f, unsigned N, int reverse, cmp_t *buf);

static void putcmp(cmp_t c)
{
  printf("%+.5f%+.5fi", (double)cmp_real(c), (double)cmp_imag(c));
}

// 将小量转化为零，使得输出数值便于阅读
static void fixzero(num_t *num, unsigned n, num_t eps)
{
  for(unsigned int i = 0; i < n; ++i) {
    if(num_abs(num[i]) < eps) num[i] = 0;
  }
}

int main(void)
{
  unsigned N = 4, n = 1 << N;
  cmp_t f[n], buf[n];

  // 填写输入
  //for(unsigned i = 0; i < n; ++i) f[i] = i;
  //for(unsigned i = 0; i < n; ++i) f[i] = cos(2 * M_PI * i / n);
  //for(unsigned i = 0; i < n; ++i) f[i] = sin(2 * M_PI * i / n);
  srand48(time(0));
  //for(unsigned i = 0; i < n; ++i) f[i] = drand48();
  for(unsigned i = 0; i < (n << 1); ++i) ((num_t *)f)[i] = drand48();
  for(unsigned i = 0; i < n; ++i) putcmp(f[i]), printf("\n");

  // 计算 FFT
  fft(f, N, 0, buf);
  fixzero((num_t *)f, n << 1, 1e-5);
  printf("\n");
  for(unsigned i = 0; i < n; ++i) putcmp(f[i]), printf("\n");

  // 计算 FFT 逆变换，附加常数因子 n
  fft(f, N, 1, 0);
  fixzero((num_t *)f, n << 1, 1e-5);
  printf("\n");
  for(unsigned i = 0; i < n; ++i) putcmp(f[i] / n), printf("\n");

  return 0;
}
