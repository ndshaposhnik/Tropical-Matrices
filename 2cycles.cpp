#include <iostream>
#include "tropicalMatrices.h"
using std::cin;
using std::cout;

int main() {
    const int n = 7;
    TropicalMatrix<2 * n - 1> A;
    for (int i = 0; i < n; i++) {
        A[i][(i + 1) % n] = 0;
    }
    for (int i = n; i < 2 * n - 2; i++) {
        A[i][i + 1] = -1;
    }
    A[0][n] = -1;
    A[2 * n - 2][0] = -1;
    cout << A << '\n';
    int sigma = n;
    auto M = (A.power(sigma)).kleene();
    std::set<size_t> g;
    for (int i = 0; i < n; i++) {
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
    cout << n << ' ' << T << ' ' << T1 << ' ' << T2 << '\n';

    return 0;
}

