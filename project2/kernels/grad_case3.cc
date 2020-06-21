#include "../run2.h"

void grad_case3(float (&B)[16][16], float (&dC)[4][16], float (&dA)[4][16]) {
  float tmpdA1[4][16];
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 16; ++j) {
      tmpdA1[i][j] = dA[i][j];
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int k = 0; k < 16; ++k) {
      for (int j = 0; j < 16; ++j) {
        tmpdA1[i][k] = (tmpdA1[i][k] + (B[k][j] * dC[i][j]));
      }
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 16; ++j) {
      dA[i][j] = tmpdA1[i][j];
    }
  }
}
