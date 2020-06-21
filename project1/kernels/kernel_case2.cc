#include "../run.h"

void kernel_case2(float (&A)[16][8]) {
  float tmp1[16][8];
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 8; ++j) {
      tmp1[i][j] = 0.0;
      tmp1[i][j] = (tmp1[i][j] + A[i][j]);
      tmp1[i][j] = (tmp1[i][j] + 2);
    }
  }
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 8; ++j) {
      A[i][j] = tmp1[i][j];
    }
  }
}
