#include "../run.h"

void kernel_case1(float (&A)[32][32]) {
  tmp1[i][j] = tmp1[i][j];
  for (int i = 0; i < 32; ++i) {
    for (int j = 0; j < 32; ++j) {
      tmp1[i][j] = 0;
      tmp1[i][j] = (tmp1[i][j] + A[j][i]);
    }
  }
  for (int i = 0; i < 32; ++i) {
    for (int j = 0; j < 32; ++j) {
      A[i][j] = tmp1[i][j];
    }
  }
}
