#include <iostream>
#include "tropicalMatrices.h"
using std::cin;
using std::cout;

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

template<size_t N>
void addCycle(TropicalMatrix<N>& A, int v, int len) {
    A[0][v] = 0;
    for (int i = 0; i < len - 2; i++) {
        A[v][v + 1] = 0;
        v += 1;
    }
    A[v][0] = 0;
}

int main() {
    const int k = 2;
    const int n = 2 * k;
    const int m = 2 * k + 2;
    TropicalMatrix<n + m - 1> A;
    addCycle(A, 1, n);
    addCycle(A, n, m);
    int sigma = gcd(n, m);
    auto M = (A.power(sigma)).kleene();
    std::set<size_t> g;
    for (int i = 0; i < n + m - 1; i++) {
        g.insert(i);
    }
    auto C = getC(M, g);
    auto S = getS(A, g);
    auto R = getR(M, g);
    auto B = getB(A, g);

    //cout << A << '\n' << M << '\n' << C << '\n' << S << '\n' << R << '\n' << B << '\n'; 
    size_t T = getT(A, C, S, R);
    size_t T1 = getT1(A, B, C, S, R);
    size_t T2 = getT2(B, C, S, R);
    int scr = A.scramblingIndex();
    cout << n + m - 1 << ' ' << T << ' ' << T1 << ' ' << scr << '\n';
    return 0;
}

