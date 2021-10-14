#pragma once
#include <vector>
#include "tropicalSemiring.h"
using std::vector;

template<size_t N, size_t M = N>
class TropicalMatrix {
private:
    vector<vector<tropical>> matrix;
public:
    TropicalMatrix() : matrix(vector<vector<tropical>>(N, vector<tropical>(M))) {}

    std::vector<tropical>& operator[] (int ind) {
        return matrix[ind];
    }

    const std::vector<tropical>& operator[] (int ind) const {
        return matrix[ind];
    }
    
    template<size_t A, size_t B>
    friend TropicalMatrix<A, B> operator + (const TropicalMatrix<A, B>&, const TropicalMatrix<A, B>&);

    template<size_t A, size_t B, size_t C>
    friend TropicalMatrix<A, C> operator * (const TropicalMatrix<A, B>&, const TropicalMatrix<B, C>&);
};

template<size_t N, size_t M>
TropicalMatrix<N, M> operator + (const TropicalMatrix<N, M>& lhs, const TropicalMatrix<N, M>& rhs) {
    TropicalMatrix<N, M> res;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            res[i][j] = lhs[i][j] + rhs[i][j];
        }
    }
    return res;
}

template<size_t N, size_t M, size_t K>
TropicalMatrix<N, K> operator * (const TropicalMatrix<N, M>& lhs, const TropicalMatrix<M, K>& rhs) {
    TropicalMatrix<N, K> res;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            for (size_t k = 0; k < M; ++k) {
                res[i][j] += (lhs[i][k] *  rhs[k][j]);
            }
        }
    }
    return res;
}

template<size_t N, size_t M>
std::ostream& operator << (std::ostream& out, const TropicalMatrix<N, M>& tm) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            out << tm[i][j];
        }
        out << '\n';
    }
    return out;
}

