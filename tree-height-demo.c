#include <stdio.h>
#include <stdlib.h>

int tree_height(const int *parent, int n);

int main(void)
{
  int n = 100;
  int *parent = (int *)malloc(n * sizeof(int));
  for(int i = 0; i < n - 1; ++i) {
    parent[i] = i + 1;
  }
  parent[n - 1] = -1;
  printf("%d\n", tree_height(parent, n));
  free(parent);
  return 0;
}
