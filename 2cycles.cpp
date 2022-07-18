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
    const int k = 7;
    const int n = 1;
    const int m = 5;
    const int N = n * k + m * k - 1;
    TropicalMatrix<N> A;
    addCycle(A, 1, n * k);
    addCycle(A, n * k, m * k);
    int sigma = gcd(n * k, m * k);
    auto M = (A.power(sigma)).kleene();
    std::set<size_t> g;
    for (int i = 0; i < N; i++) {
        g.insert(i);
    }
    auto C = getC(M, g);
    auto S = getS(A, g);
    auto R = getR(M, g);
    auto B = getB(A, g);

    //cout << A << '\n' << M << '\n' << C << '\n' << S << '\n' << R << '\n' << B << '\n'; 
    size_t T = getT(A, C, S, R);
    cout << T << '\n';
    //size_t T = ((n + 1) * m - n) * k - 1;
    //cout << A.power(T - 1)[n][N - 1] << '\n';
    return 0;
}

