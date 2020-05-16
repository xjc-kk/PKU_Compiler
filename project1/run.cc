#include <iostream>
#include <random>

#include "run.h"


bool test_example(std::mt19937 &gen, std::uniform_real_distribution<float> &dis) {
    float A[32][16] = {{0}};
    float golden[32][16] = {{0}};
    float B[32][16] = {{0}};
    float C[32][16] = {{0}};
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 16; ++j) {
            B[i][j] = dis(gen);
            C[i][j] = dis(gen);
        }
    }
    // compute golden
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 16; ++j) {
            golden[i][j] = B[i][j] * C[i][j];
        }
    }
    try {
        kernel_example(B, C, A);
    } catch (...) {
        std::cout << "Failed because of runtime error\n";
        return false;
    }

    // check
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 16; ++j) {
            if (std::abs(golden[i][j] - A[i][j]) >= 1e-5) {
                std::cout << "Wrong answer\n";
                return false;
            }
        }
    }
    // correct
    return true;
}


bool test_case1() {
    float A[32][16] = {{0}};
    float golden[32][16] = {{0}};
    // compute golden
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 16; ++j) {
            golden[i][j] = 2;
        }
    }
    try {
        kernel_case1(A);
    } catch (...) {
        std::cout << "Failed because of runtime error\n";
        return false;
    }

    // check
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 16; ++j) {
            if (std::abs(golden[i][j] - A[i][j]) >= 1e-5) {
                std::cout << "Wrong answer\n";
                return false;
            }
        }
    }
    // correct
    return true;
}


bool test_case4(std::mt19937 &gen, std::uniform_real_distribution<float> &dis) {
    float A[16][32] = {{0}};
    float B[16][32] = {{0}};
    float C[32][32] = {{0}};
    float golden[16][32] = {{0}};
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 32; ++j) {
            B[i][j] = dis(gen);
        }
    }
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 32; ++j) {
            C[i][j] = dis(gen);
        }
    }
    // compute golden
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 32; ++j) {
            for (int k = 0; k < 32; ++k) {
                golden[i][j] = golden[i][j] + B[i][k] * C[k][j];
            }
        }
    }
    try {
        kernel_case4(B, C, A);
    } catch (...) {
        std::cout << "Failed because of runtime error\n";
        return false;
    }

    // check
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 32; ++j) {
            if (std::abs(golden[i][j] - A[i][j]) >= 1e-5) {
                std::cout << "Wrong answer\n";
                return false;
            }
        }
    }
    // correct
    return true;
}


bool test_case5(std::mt19937 &gen, std::uniform_real_distribution<float> &dis) {
    float A[16][32] = {{0}};
    float B[16][32] = {{0}};
    float C[32][32] = {{0}};
    float D[16][32] = {{0}};
    float alpha = dis(gen);
    float beta = dis(gen);
    float golden[16][32] = {{0}};
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 32; ++j) {
            B[i][j] = dis(gen);
        }
    }
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 32; ++j) {
            C[i][j] = dis(gen);
        }
    }
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 32; ++j) {
            D[i][j] = dis(gen);
        }
    }
    // compute golden
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 32; ++j) {
            for (int k = 0; k < 32; ++k) {
                golden[i][j] = golden[i][j] + alpha * (B[i][k] * C[k][j]);
            }
            golden[i][j] = golden[i][j] + beta * D[i][j];
        }
    }
    try {
        kernel_case5(B, C, D, alpha, beta, A);
    } catch (...) {
        std::cout << "Failed because of runtime error\n";
        return false;
    }

    // check
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 32; ++j) {
            if (std::abs(golden[i][j] - A[i][j]) >= 1e-5) {
                std::cout << "Wrong answer\n";
                return false;
            }
        }
    }
    // correct
    return true;
}


bool test_case6(std::mt19937 &gen, std::uniform_real_distribution<float> &dis) {
    float A[2][8][5][5] = {{{{0}}}};
    float B[2][16][7][7] = {{{{0}}}};
    float C[8][16][3][3] = {{{{0}}}};
    float golden[2][8][5][5] = {{{{0}}}};
    for (int n = 0; n < 2; ++n) {
        for (int c = 0; c < 16; ++c) {
            for (int h = 0; h < 7; ++h) {
                for (int w = 0; w < 7; ++w) {
                    B[n][c][h][w] = dis(gen);
                }
            }
        }
    }
    for (int k = 0; k < 8; ++k) {
        for (int c = 0; c < 16; ++c) {
            for (int r = 0; r < 3; ++r) {
                for (int s = 0; s < 3; ++s) {
                    C[k][c][r][s] = dis(gen);
                }
            }
        }
    }
    // compute golden
    for (int n = 0; n < 2; ++n) {
        for (int k = 0; k < 8; ++k) {
            for (int p = 0; p < 5; ++p) {
                for (int q = 0; q < 5; ++q) {
                    for (int c = 0; c < 16; ++c) {
                        for (int r = 0; r < 3; ++r) {
                            for (int s = 0; s < 3; ++s) {
                                golden[n][k][p][q] = golden[n][k][p][q] + B[n][c][p+r][q+s] * C[k][c][r][s];
                            }
                        }
                    }
                }
            }
        }
    }
    try {
        kernel_case6(B, C, A);
    } catch (...) {
        std::cout << "Failed because of runtime error\n";
        return false;
    }

    // check
    for (int n = 0; n < 2; ++n) {
        for (int k = 0; k < 8; ++k) {
            for (int p = 0; p < 5; ++p) {
                for (int q = 0; q < 5; ++q) {
                    if (std::abs(golden[n][k][p][q] - A[n][k][p][q]) >= 1e-5) {
                        std::cout << "Wrong answer\n";
                        return false;
                    }
                }
            }
        }
    }
    // correct
    return true;
}


bool test_case7(std::mt19937 &gen, std::uniform_real_distribution<float> &dis) {
    float A[32][16] = {{0}};
    float B[16][32] = {{0}};
    float golden[16][32] = {{0}};
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 16; ++j) {
            A[i][j] = dis(gen);
        }
    }
    // compute golden
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 32; ++j) {
            golden[i][j] = A[j][i];
        }
    }
    try {
        kernel_case7(A, B);
    } catch (...) {
        std::cout << "Failed because of runtime error\n";
        return false;
    }

    // check
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 32; ++j) {
            if (std::abs(golden[i][j] - B[i][j]) >= 1e-5) {
                std::cout << "Wrong answer\n";
                return false;
            }
        }
    }
    // correct
    return true;
}


bool test_case10(std::mt19937 &gen, std::uniform_real_distribution<float> &dis) {
    float A[8][8] = {{0}};
    float B[10][10] = {{0}};
    float golden[8][8] = {{0}};
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            B[i][j] = dis(gen);
        }
    }
    // compute golden
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            golden[i][j] = (B[i][j] + B[i+1][j] + B[i+2][j])/3;
        }
    }
    try {
        kernel_case10(B, A);
    } catch (...) {
        std::cout << "Failed because of runtime error\n";
        return false;
    }

    // check
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (std::abs(golden[i][j] - A[i][j]) >= 1e-5) {
                std::cout << "Wrong answer\n";
                return false;
            }
        }
    }
    // correct
    return true;
}
#define rep(i, b) for (int i=0;i<b;i++)

#define INIT0(A, type)       type A = dis(gen);
#define INIT1(A, type, n)    type A[n] = {0}; rep(i, n) A[i] = dis(gen);
#define INIT2(A, type, n, m) type A[n][m] = {{0}}; rep(i, n) rep(j,m) A[i][j] = dis(gen);
#define INIT3(A, type, n, m, p) type A[n][m][p] = {{{0}}}; rep(i, n) rep(j,m) rep(k,p) A[i][j][k] = dis(gen);

#define DIFF1(golden, A, n) \
rep(i, n) \
if (std::abs(golden[i] - A[i]) >= 1e-5) \
{\
	std::cout << "Wrong answer\n";\
	return false;\
}

#define DIFF2(golden, A, n, m) \
rep(i, n) \
rep(j, m) \
if (std::abs(golden[i][j] - A[i][j]) >= 1e-5) \
{\
	std::cout << "Wrong answer\n";\
	return false;\
}


bool test_case11(std::mt19937 &gen, std::uniform_real_distribution<float> &dis)
{
	INIT1(A, int, 3);
	INIT1(B, int, 3);
	INIT2(C, int, 3, 4);
	INIT1(D, int, 8);
	INIT1(E, int, 5);
	INIT0(alpha, int);
    int golden[3] = {0};
	
	rep(i, 3)
	{
		int tmp=0;
		rep(j, 3)
			tmp += A[i] * B[j];
		rep(k, 3)
			rep(l, 8)
				tmp += C[k][l/2] + D[l];
		rep(m, 5)
			tmp -= E[m] * alpha;
        golden[i] = tmp;
	}
    try {
        kernel_case11(B, C, D, E, alpha, A);
    } catch (...) {
        std::cout << "Failed because of runtime error\n";
        return false;
    }

	DIFF1(golden, A, 3);
    // check
    // correct
    return true;
}

bool test_case12(std::mt19937 &gen, std::uniform_real_distribution<float> &dis)
{
	INIT2(A, int, 32, 32);
	INIT3(B, int, 32, 5, 32);
    int golden[32][32] = {{0}};
	
	rep(i, 32)
	rep(j, 32)
	{
		int tmp=A[j][i];
		rep(k, 5)
			tmp += B[j][k][i];
        golden[i][j] = tmp;
	}
    try {
        kernel_case12(A, B);
    } catch (...) {
        std::cout << "Failed because of runtime error\n";
        return false;
    }

	DIFF2(golden, A, 32, 32);
    // check
    // correct
    return true;
}
int main() {
    std::random_device rd;  // get random seed
    std::mt19937 gen(rd()); // standard
    std::uniform_real_distribution<float> dis(-10, 10);
    //std::uniform_real_distribution<int> dis_int(-10, 10);
    std::cout << "Random distribution ready\n";
    // example
    std::cout << "Example ";
    bool res = test_example(gen, dis);
    if (res) {
        std::cout << "Success!\n";
    }
    // cases
    std::cout << "Case 1 ";
    res = test_case1();
    if (res) {
        std::cout << "Success!\n";
    }
    std::cout << "Case 2 is hidden\n";
    std::cout << "Case 3 is hidden\n";
    std::cout << "Case 4 ";
    res = test_case4(gen, dis);
    if (res) {
        std::cout << "Success!\n";
    }
    std::cout << "Case 5 ";
    res = test_case5(gen, dis);
    if (res) {
        std::cout << "Success!\n";
    }
    std::cout << "Case 6 ";
    res = test_case6(gen, dis);
    if (res) {
        std::cout << "Success!\n";
    }
    std::cout << "Case 7 ";
    res = test_case7(gen, dis);
    if (res) {
        std::cout << "Success!\n";
    }
    std::cout << "Case 8 is hidden\n";
    std::cout << "Case 9 is hidden\n";
    std::cout << "Case 10 ";
    res = test_case10(gen, dis);
    if (res) {
        std::cout << "Success!\n";
    }

    std::cout << "Case 11 ";
	res = test_case11(gen, dis);
    if (res) {
        std::cout << "Success!\n";
    }

	std::cout << "Case 12 ";
	res = test_case12(gen, dis);
    if (res) {
        std::cout << "Success!\n";
    }
    return 0;
}
