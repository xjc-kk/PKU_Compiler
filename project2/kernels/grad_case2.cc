#include "../run2.h"

void grad_case2(float (&A)[4][16], float (&dB)[4][16], float (&dA)[4][16]) {
  float tmp1[4][16];
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 16; ++j) {
      tmp1[i][j] = 0;
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 16; ++j) {
      tmp1[i][j] = (tmp1[i][j] + ((A[i][j] + A[i][j]) * dB[i][j]));
      tmp1[i][j] = (tmp1[i][j] + (0 * dB[i][j]));
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 16; ++j) {
      dA[i][j] = tmp1[i][j];
    }
  }
}
