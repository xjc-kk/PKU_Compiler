#include "../run2.h"

void grad_case7(float (&dB)[16][32], float (&dA)[32][16]) {
  float tmpdA1[32][16];
  for (int i = 0; i < 32; ++i) {
    for (int j = 0; j < 16; ++j) {
      tmpdA1[i][j] = dA[i][j];
    }
  }
  for (int j = 0; j < 32; ++j) {
    for (int i = 0; i < 16; ++i) {
      tmpdA1[j][i] = (tmpdA1[j][i] + (1.0 * dB[i][j]));
    }
  }
  for (int i = 0; i < 32; ++i) {
    for (int j = 0; j < 16; ++j) {
      dA[i][j] = tmpdA1[i][j];
    }
  }
}
