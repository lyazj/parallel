#include "parallel.h"
#include <stdlib.h>

static int select_pivot(num_t *, int);
static int partition(num_t *, int, int);

num_t kth_smallest(num_t *arr, int n, int k)  // n >= k >= 1
{
  int ipivot = select_pivot(arr, n);
  ipivot = partition(arr, n, ipivot);
  int t = ipivot + 1;
  if(t < k) {
    return kth_smallest(arr + t, n - t, k - t);
  } else if(t > k) {
    return kth_smallest(arr, ipivot, k);
  }
  return arr[ipivot];
}

int select_pivot(num_t *, int n)
{
  return rand() % n;  // [XXX]
}

int partition(num_t *arr, int n, int p)
{
  // 取出轴值，并用尾元素代替
  num_t pivot = arr[p];
  arr[p] = arr[n - 1];

  int l = 0, r = n - 1;
  while(l != r) {
    // l 为第一个待处理值的位置，r 为最后一个待处理值后的位置
    while(l != r && arr[l] <= pivot) ++l;
    if(l == r) break;
    arr[r--] = arr[l];
    // l 为第一个待处理值前的位置，r 为最后一个待处理值的位置
    while(l != r && arr[r] >= pivot) --r;
    if(l == r) break;
    arr[l++] = arr[r];
  }

  // 填入轴值
  arr[l] = pivot;
  return l;
}
