#include <iostream>
#include "tropicalMatrices.h"
using std::cin;
using std::cout;

int main() {
    TropicalMatrix<5> A = { {0, 0, -1, _inf, -7},
                            {0, 0, -1, _inf, -7},
                            {-1, -1, -1, -3, -7},
                            {-3, _inf, _inf, -2, -7},
                            {-7, -7, -7, -7, -3} };

    int sigma = 1;
    auto M = A.kleene();
    std::set<size_t> g = {0, 1};
    auto C = getC(M, g);
    auto S = getS(A, g);
    auto R = getR(M, g);
    
    auto B = getB(A, g);
    cout << A << '\n' << M << '\n' << C << '\n' << S << '\n' << R;
    cout << getT(A, C, S, R) << '\n';

    return 0;
}
