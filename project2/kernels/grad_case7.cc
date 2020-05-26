#include "../run2.h"

void grad_case7(float (&dB)[16][32], float (&dA)[32][16]) {
  float tmp1[32][16];
  for (int i = 0; i < 32; ++i) {
    for (int j = 0; j < 16; ++j) {
      tmp1[i][j] = 0;
    }
  }
  for (int j = 0; j < 32; ++j) {
    for (int i = 0; i < 16; ++i) {
      tmp1[j][i] = (tmp1[j][i] + (1 * dB[i][j]));
    }
  }
  for (int j = 0; j < 32; ++j) {
    for (int i = 0; i < 16; ++i) {
      dA[j][i] = tmp1[j][i];
    }
  }
}
