#include "../run2.h"

void grad_case9(float (&dB)[4][6], float (&dA)[4]) {
  float tmpdA1[4];
  for (int i = 0; i < 4; ++i) {
    tmpdA1[i] = dA[i];
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 6; ++j) {
      tmpdA1[i] = (tmpdA1[i] + (1.0 * dB[i][j]));
    }
  }
  for (int i = 0; i < 4; ++i) {
    dA[i] = tmpdA1[i];
  }
}
