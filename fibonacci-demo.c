#include "parallel.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

void fibonacci(unsigned *F, unsigned n);
void fibonacci_from(unsigned *F, unsigned i, unsigned n);

int main(void)
{
  // 设置序列长度和模拟进程数，分配内存
  unsigned n = 1 << 28;
  unsigned np = 16;
  unsigned n_per_proc = n / np;
  unsigned *F0 = NULL, *F1 = NULL;
  posix_memalign((void **)&F0, getpagesize(), n * sizeof(unsigned));
  posix_memalign((void **)&F1, getpagesize(), n * sizeof(unsigned));

  // 串行结果
  fibonacci(F0, n);

  // 模拟并行结果
  unsigned offset = 0;
  for(unsigned p = 0; p < np; ++p) {
    unsigned end = p == np - 1 ? n : offset + n_per_proc;
    fibonacci_from(&F1[offset], offset, end - offset);
    offset = end;
  }

  // 检验模拟并行结果
  for(unsigned i = 0; i < n; ++i) {
    assert(F0[i] == F1[i]);
  }
  printf("Test passed!\n");

  // 清理和退出
  free(F1);
  free(F0);
  return 0;
}
