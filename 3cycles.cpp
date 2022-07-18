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

int T(int n, int m, int k) {
    if (gcd(n, m) != 1) {
        return -1;
    }
    if (m < n) {
        std::swap(m, n);
    }
    return (m * n + m - n) * k - 1;
}

int main() {
    const int n = 3; // Number of cycles!
    const int k = 5;
    const int a[n] = {2, 2, 9};
    const int N = (a[0] + a[1] + a[2]) * k - n + 1;
    TropicalMatrix<N> A;
    int tmp = 1;
    for (int i = 0; i < n; i++) {
        addCycle(A, tmp, a[i] * k);
        tmp += a[i] * k - 1;
    }
    int sigma = k;
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
    cout << getT(A, C, S, R) << std::endl;
    cout << getT1(A, B, C, S, R) << std::endl;
    cout << getT2(B, C, S, R) << std::endl;
    //size_t T = getT(A, C, S, R);
    //cout << T << '\n';
    return 0;
}

