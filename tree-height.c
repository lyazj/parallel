#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tree_height(const int *parent, int n)
{
  // 每个节点当前看到的根节点
  // 当 root[i] < 0 时上一轮迭代已经看到了根节点
  int *root = (int *)malloc(n * sizeof(int));

  // 每个节点与当前看到的根节点之间的距离
  // 当 root[i] < 0 时为节点高度
  int *height = (int *)malloc(n * sizeof(int));

  // 当前最大高度
  int max_height = 0;

  // 是否有节点看到新的根节点
  int modified;

  // 初始化 root, height 和 max_height
  for(int i = 0; i < n; ++i) {
    root[i] = parent[i];
    height[i] = root[i] >= 0;
    if(height[i]) max_height = 1;
  }

  // 使用短路策略不断更新 root, height 和 max_height
  do {
    modified = 0;
    for(int i = 0; i < n; ++i) printf("%4d", height[i]);
    printf("\n");
    for(int i = 0; i < n; ++i) {
      if(root[i] < 0) continue;  // 之前已经到达过根节点
      height[i] += height[root[i]];
      root[i] = root[root[i]];
      if(height[i] > max_height) max_height = height[i];
      modified = 1;
    }
  } while(modified);

  free(height);
  free(root);
  return max_height;
}
