#include "../run2.h"

void grad_case4(float (&B)[16][32], float (&C)[32][32], float (&dA)[16][32], float (&dB)[16][32], float (&dC)[32][32]) {
  float tmpdB1[16][32];
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 32; ++j) {
      tmpdB1[i][j] = dB[i][j];
    }
  }
  for (int i = 0; i < 16; ++i) {
    for (int k = 0; k < 32; ++k) {
      for (int j = 0; j < 32; ++j) {
        tmpdB1[i][k] = (tmpdB1[i][k] + (C[k][j] * dA[i][j]));
      }
    }
  }
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 32; ++j) {
      dB[i][j] = tmpdB1[i][j];
    }
  }
  float tmpdC2[32][32];
  for (int i = 0; i < 32; ++i) {
    for (int j = 0; j < 32; ++j) {
      tmpdC2[i][j] = dC[i][j];
    }
  }
  for (int k = 0; k < 32; ++k) {
    for (int j = 0; j < 32; ++j) {
      for (int i = 0; i < 16; ++i) {
        tmpdC2[k][j] = (tmpdC2[k][j] + (B[i][k] * dA[i][j]));
      }
    }
  }
  for (int i = 0; i < 32; ++i) {
    for (int j = 0; j < 32; ++j) {
      dC[i][j] = tmpdC2[i][j];
    }
  }
}
