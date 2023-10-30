#define M  998244353

void fibonacci(unsigned *F, unsigned n)
{
  if(n == 0) return;
  F[0] = 0;
  if(n == 1) return;
  F[1] = 1;
  unsigned F0 = 0, F1 = 1;
  for(unsigned i = 2; i < n; ++i) {
    unsigned F2 = (F0 + F1) % M;
    F[i] = F2;
    F0 = F1, F1 = F2;
  }
}

/*
 * [ F[i  ] ] =  [ 0 1 ]^i [ 0 ]
 * [ F[i+1] ]    [ 1 1 ]   [ 1 ]
 */
void fibonacci_from(unsigned *F, unsigned i, unsigned n)
{
  // 通过快速幂计算 F[i] 和 F[i+1]
  if(n == 0) return;
  unsigned long A00 = 0, A01 = 1, A10 = 1, A11 = 1;
  unsigned long T00 = 1, T01 = 0, T10 = 0, T11 = 1;
  while(i) {
    if(i & 1) {  // T *= A
      unsigned long B00 = (T00 * A00 + T01 * A10) % M;
      unsigned long B01 = (T00 * A01 + T01 * A11) % M;
      unsigned long B10 = (T10 * A00 + T11 * A10) % M;
      unsigned long B11 = (T10 * A01 + T11 * A11) % M;
      T00 = B00, T01 = B01, T10 = B10, T11 = B11;
    }
    i >>= 1;
    // A *= A
    unsigned long B00 = (A00 * A00 + A01 * A10) % M;
    unsigned long B01 = (A00 * A01 + A01 * A11) % M;
    unsigned long B10 = (A10 * A00 + A11 * A10) % M;
    unsigned long B11 = (A10 * A01 + A11 * A11) % M;
    A00 = B00, A01 = B01, A10 = B10, A11 = B11;
  }
  F[0] = T01;
  if(n == 1) return;
  F[1] = T11;

  // 通过递推公式计算后续序列
  unsigned F0 = T01, F1 = T11;
  for(i = 2; i < n; ++i) {
    unsigned F2 = (F0 + F1) % M;
    F[i] = F2;
    F0 = F1, F1 = F2;
  }
}
