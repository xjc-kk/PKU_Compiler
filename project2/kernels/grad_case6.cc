#include "../run2.h"

void grad_case6(float (&C)[8][16][3][3], float (&dA)[2][8][5][5], float (&dB)[2][16][7][7]) {
  float tmp1[2][16][7][7];
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 16; ++j) {
      for (int k = 0; k < 7; ++k) {
        for (int l = 0; l < 7; ++l) {
          tmp1[i][j][k][l] = 0;
        }
      }
    }
  }
  for (int n = 0; n < 2; ++n) {
    for (int c = 0; c < 16; ++c) {
      for (int p = 0; p < 5; ++p) {
        for (int r = 0; r < 3; ++r) {
          for (int q = 0; q < 5; ++q) {
            for (int s = 0; s < 3; ++s) {
              for (int k = 0; k < 8; ++k) {
                if (((q + s) < 7 && (q + s) >= 0)) {
                  if (((p + r) < 7 && (p + r) >= 0)) {
                    tmp1[n][c][(p + r)][(q + s)] = (tmp1[n][c][(p + r)][(q + s)] + (C[k][c][r][s] * dA[n][k][p][q]));
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  for (int n = 0; n < 2; ++n) {
    for (int c = 0; c < 16; ++c) {
      for (int p = 0; p < 5; ++p) {
        for (int r = 0; r < 3; ++r) {
          for (int q = 0; q < 5; ++q) {
            for (int s = 0; s < 3; ++s) {
              dB[n][c][(p + r)][(q + s)] = tmp1[n][c][(p + r)][(q + s)];
            }
          }
        }
      }
    }
  }
}
