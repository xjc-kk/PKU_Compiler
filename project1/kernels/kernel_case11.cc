#include "../run.h"

void kernel_case11(int (&B)[3], int (&C)[3][4], int (&D)[8], int (&E)[5], int (&alpha), int (&A)[3]) {
  int tmp1[3];
  for (int i = 0; i < 3; ++i) {
    tmp1[i] = 0;
    for (int j = 0; j < 3; ++j) {
      tmp1[i] = (tmp1[i] + (A[i] * B[j]));
    }
    for (int k = 0; k < 3; ++k) {
      for (int l = 0; l < 8; ++l) {
        if (((l / 2) < 4 && (l / 2) >= 0)) {
          tmp1[i] = (tmp1[i] + (C[k][(l / 2)] + D[l]));
        }
      }
    }
    for (int m = 0; m < 5; ++m) {
      tmp1[i] = (tmp1[i] + (-(E[m] * alpha)));
    }
  }
  for (int i = 0; i < 3; ++i) {
    A[i] = tmp1[i];
  }
}
