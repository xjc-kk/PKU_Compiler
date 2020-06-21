#include "../run2.h"

void grad_case8(float (&dB)[32], float (&dA)[2][16]) {
  float tmpdA1[2][16];
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 16; ++j) {
      tmpdA1[i][j] = dA[i][j];
    }
  }
  for (int i = 0; i < 32; ++i) {
    int u;
    u = (i / 16);
    int v;
    v = (i % 16);
    if (((i % 16) < 16 && (i % 16) >= 0)) {
      if (((i / 16) < 2 && (i / 16) >= 0)) {
        tmpdA1[u][v] = (tmpdA1[(i / 16)][(i % 16)] + (1.0 * dB[i]));
      }
    }
  }
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 16; ++j) {
      dA[i][j] = tmpdA1[i][j];
    }
  }
}
