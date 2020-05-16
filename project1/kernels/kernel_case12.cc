#include "../run.h"

void kernel_case12(int (&A)[32][32], int (&B)[32][5][32]) {
  int tmp1[32][32];
  for (int i = 0; i < 32; ++i) {
    for (int j = 0; j < 32; ++j) {
      tmp1[i][j] = 0;
      tmp1[i][j] = (tmp1[i][j] + A[j][i]);
      for (int k = 0; k < 5; ++k) {
        tmp1[i][j] = (tmp1[i][j] + B[j][k][i]);
      }
    }
  }
  for (int i = 0; i < 32; ++i) {
    for (int j = 0; j < 32; ++j) {
      A[i][j] = tmp1[i][j];
    }
  }
}
