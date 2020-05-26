#include "../run2.h"

void grad_case3(float (&B)[16][16], float (&dC)[4][16], float (&dA)[4][16]) {
  float tmp1[4][16];
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 16; ++j) {
      tmp1[i][j] = 0;
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int k = 0; k < 16; ++k) {
      for (int j = 0; j < 16; ++j) {
        tmp1[i][k] = (tmp1[i][k] + (B[k][j] * dC[i][j]));
      }
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int k = 0; k < 16; ++k) {
      dA[i][k] = tmp1[i][k];
    }
  }
}
