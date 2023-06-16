//Luogu - P2461
#include<bits/stdc++.h>

#include <iostream>
#include <vector>

namespace DEBUG {
    template<typename T>
    inline void _debug(const char *format, T t) {
        std::cerr << format << '=' << t << std::endl;
    }

    template<class First, class... Rest>
    inline void _debug(const char *format, First first, Rest... rest) {
        while (*format != ',') std::cerr << *format++;
        std::cerr << '=' << first << ",";
        _debug(format + 1, rest...);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
        os << "[ ";
        for (const auto &vv: V) os << vv << ", ";
        os << "]";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, __int128 V) {
        if (V < 0) {
            os << '-';
            V = -V;
        }

        if (V > 9)
            os << V / 10;

        os << (int) (V % 10);

        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

valueType MOD_;
valueType const &MOD = MOD_;

class Matrix {
public:
    typedef long long valueType;
    typedef valueType &reference;
    typedef size_t sizeType;
    typedef std::vector<valueType> Row;
    typedef std::vector<Row> Container;
    valueType MOD = ::MOD;

    enum TYPE : int {
        EMPTY = 0, UNIT = 1
    };

protected:
    sizeType _row_, _column_;
    Container data;

public:
    Matrix(sizeType row, sizeType column) : _row_(row), _column_(column), data(_row_) {
        for (auto &iter: data)
            iter.resize(column, 0);
    };

    sizeType row() const {
        return _row_;
    }

    sizeType column() const {
        return _column_;
    }

    void set(TYPE type) {
        for (auto &iter: data) {
            std::fill(iter.begin(), iter.end(), 0);
        }

        if (type == EMPTY)
            return;

        if (type == UNIT)
            for (sizeType i = 0, end = std::min(_row_, _column_); i < end; ++i)
                data[i][i] = 1;
    }

    reference operator()(sizeType i, sizeType j) {
        if (i > this->_row_ || j > this->_column_)
            throw std::out_of_range("Too Large.");

        if (i == 0 || j == 0)
            throw std::out_of_range("0 index access.");

        return std::ref(data[i - 1][j - 1]);
    }

    Matrix operator+(const Matrix &T) const {
        if (this->_row_ != T._row_ || this->_column_ != T._column_)
            throw std::range_error("Illegal operation.");

        Matrix result(this->_row_, this->_column_);

        for (sizeType i = 0; i < this->_row_; ++i)
            for (sizeType j = 0; j < this->_column_; ++j)
                result.data[i][j] = (this->data[i][j] + T.data[i][j]) % MOD;

        return result;
    }

    Matrix operator*(const Matrix &T) const {
        if (this->_column_ != T._row_)
            throw std::range_error("Illegal operation.");

        Matrix result(this->_row_, T._column_);

        for (sizeType i = 0; i < this->_row_; ++i) {
            for (sizeType k = 0; k < this->_column_; ++k) {
                valueType r = this->data[i][k];

                for (sizeType j = 0; j < T._column_; ++j)
                    result.data[i][j] = (result.data[i][j] + T.data[k][j] * r) % MOD;
            }
        }

        return result;
    }

    Matrix operator^(valueType x) const {
        if (x < 1)
            throw std::range_error("Illegal operation.");

        Matrix result(this->_row_, this->_column_);
        Matrix base = *this;

        result.set(UNIT);

        while (x) {
            if (x & 1) result = result * base;

            base = base * base;

            x = x >> 1;
        }

        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &T) {
        for (sizeType i = 0; i < T._row_; ++i)
            for (sizeType j = 0; j < T._column_; ++j)
                os << T.data[i][j] << " \n"[j == T._column_ - 1];

        return os;
    }

    friend std::istream &operator>>(std::istream &os, Matrix &T) {
        for (sizeType i = 0; i < T._row_; ++i)
            for (sizeType j = 0; j < T._column_; ++j)
                os >> T.data[i][j];

        return os;
    }
};

int main() {
    valueType K, M, N;

    std::cin >> K;

    ValueVector B(K + 30, 0), C(K + 30, 0);

    for (int i = 1; i <= K; ++i)
        std::cin >> B[i];

    for (int i = 1; i <= K; ++i)
        std::cin >> C[i];

    std::cin >> M >> N >> MOD_;

    for (int i = 1; i <= K; ++i) {
        B[i] %= MOD;
        C[i] %= MOD;
    }

    Matrix ans(1, K + 1), base(K + 1, K + 1);

    ans.set(Matrix::EMPTY);
    base.set(Matrix::EMPTY);

    for (int i = 1; i <= K; ++i)
        base(i, 1) = C[i];

    for (int i = 2; i <= K; ++i)
        base(i - 1, i) = 1;

    base(1, K + 1) = base(K + 1, K + 1) = 1;

    for (int i = 1; i <= K; ++i)
        ans(1, K + 1 - i) = B[i];

    ans(1, K + 1) = std::accumulate(B.begin() + 1, B.begin() + K, 0) % MOD;
    valueType resultN = 0, resultM = 0;

    ++N;
    if (N > K) {
        Matrix MatrixN = ans * (base ^ (N - K));

        resultN = MatrixN(1, K + 1);
    } else {
        resultN = std::accumulate(B.begin() + 1, B.begin() + N, 0);
    }

    if (M > K) {
        Matrix MatrixM = ans * (base ^ (M - K));

        resultM = MatrixM(1, K + 1);
    } else {
        resultM = std::accumulate(B.begin() + 1, B.begin() + M, 0);
    }

    valueType result = resultN - resultM;

    result = (result % MOD + MOD) % MOD;

    std::cout << result << std::flush;

    return 0;
}
