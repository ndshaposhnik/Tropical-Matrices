#pragma once
#include <vector>
#include "tropicalSemiring.h"

template<size_t N, size_t M = N>
class TropicalMatrix {
private:
    std::vector<std::vector<Tropical>> matrix;
public:
    TropicalMatrix() : matrix(std::vector<std::vector<Tropical>>(N, std::vector<Tropical>(M))) {}

    TropicalMatrix(const std::initializer_list<std::vector<Tropical>>& list) {
        std::vector<std::vector<Tropical>> tmp(list);
        matrix.resize(N, std::vector<Tropical>(M));
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                matrix[i][j] = tmp[i][j];
            }
        }
    }

    std::vector<Tropical>& operator[] (int ind) {
        return matrix[ind];
    }

    const std::vector<Tropical>& operator[] (int ind) const {
        return matrix[ind];
    }

    template<size_t A, size_t B>
    friend TropicalMatrix<A, B> operator + (const TropicalMatrix<A, B>&, const TropicalMatrix<A, B>&);

    template<size_t A, size_t B, size_t C>
    friend TropicalMatrix<A, C> operator * (const TropicalMatrix<A, B>&, const TropicalMatrix<B, C>&);

    TropicalMatrix operator += (const TropicalMatrix<N, M>& rhs) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                (*this)[i][j] += rhs[i][j];
            }
        }
        return *this;
    }

    template<size_t K>
    TropicalMatrix operator *= (const TropicalMatrix<M, K>& rhs) {
        *this = *this * rhs;
        return *this;
    }

    static TropicalMatrix<N, N> unit() {
        TropicalMatrix<N, N> res;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                res[i][j] = _inf;
            }
        }
        for (size_t i = 0; i < N; ++i) {
            res[i][i] = 0;
        }
        return res;
    }

    TropicalMatrix<N, N> kleene() const {
        TropicalMatrix<N> res, tmp = unit();
        for (size_t i = 0; i < N; ++i) {
            res += tmp;
            tmp *= (*this);
        }
        return res;
    }

    TropicalMatrix<N, N> power(size_t n) const {
        if (n == 0) {
            return unit();
        }
        if (n == 1) {
            return *this;
        }
        if (n % 2 == 0) {
            return ((*this) * (*this)).power(n / 2);
        }
        return (*this) * power(n - 1);
    }
};

template<size_t N, size_t M>
TropicalMatrix<N, M> operator + (const TropicalMatrix<N, M>& lhs, const TropicalMatrix<N, M>& rhs) {
    TropicalMatrix<N, M> res = lhs;
    res += rhs;
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

