#include "parallel.h"
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

/*
 * Compute prefix sum of an array sequentially.
 * Expect n >= 0.
 */
typedef struct { num_t *arr; int n; } presum_seq_args_t;
static void *presum_seq(void *v_args)
{
  presum_seq_args_t *args = v_args;
  num_t *arr = args->arr; int n = args->n;
  num_t t = 0;
  for(int i = 0; i < n; ++i) {
    t += arr[i];
    arr[i] = t;
  }
  return NULL;
}

/*
 * Add num to each element of an array sequentially.
 * Expect n >= 0.
 */
typedef struct { num_t *arr; int n; num_t num; } add_seq_args_t;
static void *add_seq(void *v_args)
{
  add_seq_args_t *args = v_args;
  num_t *arr = args->arr; int n = args->n; num_t num = args->num;
  for(int i = 0; i < n; ++i) {
    arr[i] += num;
  }
  return NULL;
}

/*
 * Compute prefix sum of an array threadingly.
 * Expect n >= 0 and nthr > 0.
 */
void presum_thr(num_t *arr, int n, int nthr)
{
  // Allocate memory for working threads and arguments.
  pthread_t *thr = malloc(nthr * sizeof(pthread_t));
  presum_seq_args_t *ps_args = malloc(nthr * sizeof(presum_seq_args_t));
  add_seq_args_t *as_args = malloc((nthr - 1) * sizeof(add_seq_args_t));
  if(thr == NULL || ps_args == NULL || as_args == NULL) abort();

  // Compute bunch size for each thread.
  int bunch_size = (n + nthr) / (nthr + 1);

  // Compute prefix sums of the first nthr bunches concurrently.
  for(int t = 0, last = 0; t < nthr; ++t) {
    int end = last + bunch_size;
    if(end > n) end = n;
    ps_args[t].arr = &arr[last];
    ps_args[t].n = end - last;
    last = end;
    if(pthread_create(&thr[t], NULL, presum_seq, &ps_args[t])) abort();
  }
  for(int t = 0; t < nthr; ++t) {
    if(pthread_join(thr[t], NULL)) abort();
  }

  // Get overall prefix sum based on separated bunches.
  num_t last_sum = 0;
  for(int t = 0, last = bunch_size; t < nthr; ++t) {
    last_sum += arr[last - 1];
    int end = last + bunch_size;
    if(end > n) end = n;
    if(t == nthr - 1) {
      if(last < n) arr[last] += last_sum;
      ps_args[t].arr = &arr[last];
      ps_args[t].n = end - last;
      if(pthread_create(&thr[t], NULL, presum_seq, &ps_args[t])) abort();
    } else {
      as_args[t].arr = &arr[last];
      as_args[t].n = end - last;
      as_args[t].num = last_sum;
      if(pthread_create(&thr[t], NULL, add_seq, &as_args[t])) abort();
    }
    last = end;
  }
  for(int t = 0; t < nthr; ++t) {
    if(pthread_join(thr[t], NULL)) abort();
  }

  // Clean up.
  free(as_args);
  free(ps_args);
  free(thr);
}
