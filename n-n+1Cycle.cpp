#include <iostream>
#include "tropicalMatrices.h"
using std::cin;
using std::cout;

int main() {
    const int n = 8;
    TropicalMatrix<2 * n> A;
    for (int i = 0; i <= n; i++) {
        A[i][(i + 1) % (n + 1)] = 0;
    }
    for (int i = n + 1; i < 2 * n - 1; i++) {
        A[i][i + 1] = 0;
    }
    A[0][n + 1] = 0;
    A[2 * n - 1][0] = 0;
    int exp = A.exponent();
    cout << exp << '\n';
    int scr = A.scramblingIndex();
    cout << scr << ' ';
    if (n % 2 == 0) {
        cout << n * (n + 2) / 2 << '\n';
    } else {
        cout << (n * n + 2 * n - 1) / 2 << '\n';
    }
    return 0;
    int sigma = 1;
    auto M = (A.power(sigma)).kleene();
    std::set<size_t> g;
    for (int i = 0; i < 2 * n; i++) {
        g.insert(i);
    }
    auto C = getC(M, g);
    auto S = getS(A, g);
    auto R = getR(M, g);
    auto B = getB(A, g);

    // cout << A << '\n' << M << '\n' << C << '\n' << S << '\n' << R << '\n' << B << '\n'; 
    size_t T = getT(A, C, S, R);
    size_t T1 = getT1(A, B, C, S, R);
    size_t T2 = getT2(B, C, S, R);
    //cout << (A^(T1 - 1)) << '\n' << C*(S^(T1-1))*R << '\n';
    cout << n << ' ' << T << ' ' << T1 << ' ' << T2 << '\n';
    /*auto AT1m1 = A^(T1 - 1);
    auto CST1m1R = C*(S^(T1-1))*R;
    for (int i = 0; i < 2 * n - 1; i++) {
        for (int j = 0; j < 2 * n - 1; j++) {
            if (AT1m1[i][j] != CST1m1R[i][j]) {
                cout << i + 1 << ' ' << j + 1 << '\n';
                return 0;
            }
        }
    }*/
    return 0;
}

