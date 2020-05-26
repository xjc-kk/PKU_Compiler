#include "../run2.h"

void grad_case10(float (&dA)[8][8], float (&dB)[10][8]) {
  float tmp1[10][8];
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 8; ++j) {
      tmp1[i][j] = 0;
    }
  }
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (((i + 2) < 10 && (i + 2) >= 0)) {
        tmp1[(i + 2)][j] = (tmp1[(i + 2)][j] + ((((1 + 1) + 1) / 3) * dA[i][j]));
      }
    }
  }
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      dB[(i + 2)][j] = tmp1[(i + 2)][j];
    }
  }
}
