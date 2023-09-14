#include "parallel.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  num_t *A; int hA, wA;
  num_t *B; int hB, wB;
  num_t *C; int hC, wC;
} conv2d_seq_args_t;
void *conv2d_seq(void *v_args);

int main(void)
{
  /* Initialize operands. */
  int hA = 3, wA = 2, hB = 2, wB = 3;
  num_t A[hA * wA], B[hB * wB];
  for(int i = 0; i < hA * wA; ++i) A[i] = i;
  for(int i = 0; i < hB * wB; ++i) B[i] = i;

  /* Compute (C = A conv B) */
  conv2d_seq_args_t args = {
    A, hA, wA, B, hB, wB, NULL, 0, 0
  };
  conv2d_seq(&args);
  int hC = args.hC, wC = args.wC;
  num_t *C = args.C;

  /* Output results. */
  for(int xC = 0; xC < hC; ++xC) {
    for(int yC = 0; yC < wC; ++yC) {
      printf("%8g", C[xC*wC + yC]);
    }
    printf("\n");
  }

  free(C);
  return 0;
}
