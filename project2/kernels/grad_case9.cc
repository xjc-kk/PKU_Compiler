#include "../run2.h"

void grad_case9(float (&dB)[4][6], float (&dA)[4]) {
  float tmp1[4];
  for (int i = 0; i < 4; ++i) {
    tmp1[i] = 0;
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 6; ++j) {
      tmp1[i] = (tmp1[i] + (1 * dB[i][j]));
    }
  }
  for (int i = 0; i < 4; ++i) {
    dA[i] = tmp1[i];
  }
}
