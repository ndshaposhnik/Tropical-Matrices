#include <iostream>
#include "tropicalMatrices.h"
using std::cin;
using std::cout;

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
    const int k = 8;
    const int n = 5 * k - 2;
    const int lengths[3] = {1, 1, 3};
    TropicalMatrix<n> A;
    addCycle(A, 1, k);
    addCycle(A, k, 2 * k);
    addCycle(A, 2 * k - 1, 3 * k);
    cout << A << '\n';
    int sigma = k;
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

