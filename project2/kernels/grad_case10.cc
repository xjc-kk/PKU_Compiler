#include "../run2.h"

void grad_case10(float (&dA)[8][8], float (&dB)[10][8]) {
  float tmpdB1[10][8];
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 8; ++j) {
      tmpdB1[i][j] = dB[i][j];
    }
  }
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      tmpdB1[i][j] = (tmpdB1[i][j] + ((((1.0 + 0.0) + 0.0) / 3.0) * dA[i][j]));
    }
  }
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 8; ++j) {
      dB[i][j] = tmpdB1[i][j];
    }
  }
  float tmpdB2[10][8];
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 8; ++j) {
      tmpdB2[i][j] = dB[i][j];
    }
  }
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      int u;
      u = (i + 1);
      int v;
      v = j;
      if (((i + 1) < 10 && (i + 1) >= 0)) {
        tmpdB2[u][v] = (tmpdB2[(i + 1)][j] + ((((0.0 + 1.0) + 0.0) / 3.0) * dA[i][j]));
      }
    }
  }
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 8; ++j) {
      dB[i][j] = tmpdB2[i][j];
    }
  }
  float tmpdB3[10][8];
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 8; ++j) {
      tmpdB3[i][j] = dB[i][j];
    }
  }
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      int u;
      u = (i + 2);
      int v;
      v = j;
      if (((i + 2) < 10 && (i + 2) >= 0)) {
        tmpdB3[u][v] = (tmpdB3[(i + 2)][j] + (((0 + 1.0) / 3.0) * dA[i][j]));
      }
    }
  }
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 8; ++j) {
      dB[i][j] = tmpdB3[i][j];
    }
  }
}
