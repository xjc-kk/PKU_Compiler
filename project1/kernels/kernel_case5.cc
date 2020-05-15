#include "../run.h"

void kernel_case5(float (&B)[16][32], float (&C)[32][32], float (&D)[16][32], float (&alpha), float (&beta), float (&A)[16][32]) {
  tmp1[i][j] = tmp1[i][j];
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 32; ++j) {
      tmp1[i][j] = 0;
      tmp1[i][j] = (tmp1[i][j] + A[i][j]);
      for (int k = 0; k < 32; ++k) {
        tmp1[i][j] = (tmp1[i][j] + (alpha * (B[i][k] * C[k][j])));
      }
    }
  }
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 32; ++j) {
      A[i][j] = tmp1[i][j];
    }
  }
  tmp2[i][j] = tmp2[i][j];
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 32; ++j) {
      tmp2[i][j] = 0;
      tmp2[i][j] = (tmp2[i][j] + A[i][j]);
      tmp2[i][j] = (tmp2[i][j] + (beta * D[i][j]));
    }
  }
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 32; ++j) {
      A[i][j] = tmp2[i][j];
    }
  }
}
