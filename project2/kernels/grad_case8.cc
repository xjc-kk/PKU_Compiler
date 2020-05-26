#include "../run2.h"

void grad_case8(float (&dB)[32], float (&dA)[2][16]) {
  float tmp1[2][16];
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 16; ++j) {
      tmp1[i][j] = 0;
    }
  }
  for (int i = 0; i < 32; ++i) {
    if (((i % 16) < 16 && (i % 16) >= 0)) {
      if (((i / 16) < 2 && (i / 16) >= 0)) {
        tmp1[(i / 16)][(i % 16)] = (tmp1[(i / 16)][(i % 16)] + (1 * dB[i]));
      }
    }
  }
  for (int i = 0; i < 32; ++i) {
    dA[(i / 16)][(i % 16)] = tmp1[(i / 16)][(i % 16)];
  }
}
