#include "../run2.h"

void grad_case1(float (&B)[4][16], float (&dC)[4][16], float (&dA)[4][16]) {
  float tmp1[4][16];
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 16; ++j) {
      tmp1[i][j] = 0;
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 16; ++j) {
      tmp1[i][j] = (tmp1[i][j] + (B[i][j] * dC[i][j]));
      tmp1[i][j] = (tmp1[i][j] + (0 * dC[i][j]));
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 16; ++j) {
      dA[i][j] = tmp1[i][j];
    }
  }
}
