#include "../run2.h"

void grad_case4(float (&B)[16][32], float (&C)[32][32], float (&dA)[16][32], float (&dB)[16][32], float (&dC)[32][32]) {
  float tmp1[16][32];
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 32; ++j) {
      tmp1[i][j] = 0;
    }
  }
  for (int i = 0; i < 16; ++i) {
    for (int k = 0; k < 32; ++k) {
      for (int j = 0; j < 32; ++j) {
        tmp1[i][k] = (tmp1[i][k] + (C[k][j] * dA[i][j]));
      }
    }
  }
  for (int i = 0; i < 16; ++i) {
    for (int k = 0; k < 32; ++k) {
      dB[i][k] = tmp1[i][k];
    }
  }
  float tmp2[32][32];
  for (int i = 0; i < 32; ++i) {
    for (int j = 0; j < 32; ++j) {
      tmp2[i][j] = 0;
    }
  }
  for (int k = 0; k < 32; ++k) {
    for (int j = 0; j < 32; ++j) {
      for (int i = 0; i < 16; ++i) {
        tmp2[k][j] = (tmp2[k][j] + (B[i][k] * dA[i][j]));
      }
    }
  }
  for (int k = 0; k < 32; ++k) {
    for (int j = 0; j < 32; ++j) {
      dC[k][j] = tmp2[k][j];
    }
  }
}
