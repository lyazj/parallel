#undef __cplusplus
#include "parallel.h"
#include <math.h>
#include <complex.h>
#include <stdlib.h>

static unsigned bitswap(unsigned n, unsigned N)
{
  unsigned s = 0;
  while(N--) s <<= 1, s |= n & 1, n >>= 1;
  return s;
}

static void swap(cmp_t *f, unsigned i, unsigned j)
{
  cmp_t fi = f[i], fj = f[j];
  f[i] = fj, f[j] = fi;
}

void fft(cmp_t *f, unsigned N, int reverse, cmp_t *buf)
{
  unsigned n = 1 << N;  // 数组规模

  // 元素交换至归并所需顺序
  for(unsigned i = 0; i < n; ++i) {
    unsigned j = bitswap(i, N);
    if(i < j) swap(f, i, j);
  }

  // 计算归并系数 w
  cmp_t *w = buf;
  if(w == NULL) w = (cmp_t *)malloc(n * sizeof(cmp_t));
  cmp_t w1 = cmp_exp((reverse ? 2 : -2) * M_PI / n * I), w0 = 1;
  for(unsigned int i = 0; i < n; ++i) {
    w[i] = w0, w0 *= w1;
  }

  // 分 N 步实施归并
  for(unsigned K = N, m = 1; m < n; m <<= 1) {
    --K;
    for(unsigned k = 0; k < n; ++k) {
      unsigned p = k ^ m;  // pear 元素
      if(k >= p) continue;  // 要求 k < p
      cmp_t fk = f[k], fp = f[p];
      fp *= w[(k << K) & (n - 1)];
      f[k] = fk + fp;
      f[p] = fk - fp;
    }
  }

  // 回收资源
  if(buf == NULL) free(w);
}
