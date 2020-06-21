#include "../run2.h"

void grad_case5(float (&C)[32][32], float (&D)[4][32], float (&dA)[16][32], float (&dB)[16][32][4]) {
  float tmpdB1[16][32][4];
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 32; ++j) {
      for (int k = 0; k < 4; ++k) {
        tmpdB1[i][j][k] = dB[i][j][k];
      }
    }
  }
  for (int i = 0; i < 16; ++i) {
    for (int k = 0; k < 32; ++k) {
      for (int l = 0; l < 4; ++l) {
        for (int j = 0; j < 32; ++j) {
          tmpdB1[i][k][l] = (tmpdB1[i][k][l] + ((C[k][j] * D[l][j]) * dA[i][j]));
        }
      }
    }
  }
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 32; ++j) {
      for (int k = 0; k < 4; ++k) {
        dB[i][j][k] = tmpdB1[i][j][k];
      }
    }
  }
}
