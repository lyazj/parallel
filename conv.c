#include "parallel.h"
#include <stdlib.h>
#include <string.h>

/*
 * Compute 2D convolution sequentially.
 */
typedef struct {
  num_t *A; int hA, wA;
  num_t *B; int hB, wB;
  num_t *C; int hC, wC;
} conv2d_seq_args_t;
void *conv2d_seq(void *v_args)
{
  /* Compute shape of C and allocate memory on demand. */
  conv2d_seq_args_t *args = (conv2d_seq_args_t *)v_args;
  int hC = args->hA + args->hB - 1, wC = args->wA + args->wB - 1;
  num_t *C = args->C;
  if(C == NULL) {
    C = (num_t *)malloc(hC * wC * sizeof(num_t));
    args->C = C;
  }
  args->hC = hC, args->wC = wC;
  memset(C, 0, hC * wC * sizeof(num_t));

  /* Iterate over B elements. */
  for(int xB = 0; xB < args->hB; ++xB) {
  for(int yB = 0; yB < args->wB; ++yB) {

    /* Iterate over A elements. */
    for(int xA = 0; xA < args->hA; ++xA) {
    for(int yA = 0; yA < args->wA; ++yA) {

      /*
       * Position of current A element W.R.T. top left corner of the core:
       *   x1 = hB - 1 - xB
       *   y1 = wB - 1 - yB
       * So top left corner of the core locates at:
       *   x0 = xA - x1 = xA - hB + xB + 1
       *   y0 = yA - y1 = yA - wB + yB + 1
       * Then bottom right corner of the core locates at:
       *   x = x0 + hB - 1 = xA + xB
       *   y = y0 + wB - 1 = yA + yB
       */
      int x = xA + xB, y = yA + yB;
      C[x*wC + y] += args->A[xA*args->wA + yA] * args->B[xB*args->wB + yB];

    } }

  } }

  return NULL;
}
