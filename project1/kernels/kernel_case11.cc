#include "../run.h"

void kernel_case11(float (&B)[3], float (&C)[3][4], float (&D)[8], float (&E)[5], float (&alpha), float (&A)[3]) {
  float tmp1[3];
  for (int i = 0; i < 3; ++i) {
    tmp1[i] = 0;
    for (int j = 0; j < 3; ++j) {
      tmp1[i] = (tmp1[i] + B[j]);
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
