//Luogu - P7453
#include <bits/stdc++.h>

constexpr long long MOD = 998244353;

class Matrix {
public:
    typedef long long valueType;
    typedef valueType &reference;
    typedef size_t sizeType;
    typedef std::vector<valueType> Row;
    typedef std::vector<Row> Container;
    constexpr static valueType const MOD = ::MOD;

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
                os << T.data[i][j] << " \n"[j == T._column_];

        return os;
    }

    friend std::istream &operator>>(std::istream &os, Matrix &T) {
        for (sizeType i = 0; i < T._row_; ++i)
            for (sizeType j = 0; j < T._column_; ++j)
                os >> T.data[i][j];

        return os;
    }
};

class SegmentTree {
public:
    typedef long long valueType;
    constexpr static valueType const MOD = ::MOD;

private:
    class Data;

    class Lazy;

    class Data {
    private:
        Matrix matrix;

    public:
        Data() : matrix(1, 4) {
            matrix(1, 1) = matrix(1, 2) = matrix(1, 3) = 0;
            matrix(1, 4) = 1;
        };

        valueType ans() {
            return (matrix(1, 1) + matrix(1, 2) + matrix(1, 3)) % MOD;
        }

        void effect(const Lazy &T) {
            matrix = matrix * T.matrix;
        }
    };

    class Lazy {
    protected:
        Matrix matrix;

    public:
        Lazy() : matrix(4, 4) {};

        explicit Lazy(int type, valueType value = 0) : matrix(4, 4) {
            if (type == 1) {
                matrix.set(Matrix::UNIT);

                matrix(2, 1) = 1;
            } else if (type == 2) {
                matrix.set(Matrix::UNIT);

                matrix(3, 2) = 1;
            } else if (type == 3) {
                matrix.set(Matrix::UNIT);

                matrix(1, 3) = 1;
            } else if (type == 4) {
                matrix.set(Matrix::UNIT);

                matrix(4, 1) = value;
            } else if (type == 5) {
                matrix.set(Matrix::UNIT);

                matrix(2, 2) = value;
            } else if (type == 6) {
                matrix.set(Matrix::UNIT);

                matrix(3, 3) = 0;
                matrix(3, 4) = value;
            }
        };

        valueType ans() {
            return (matrix(1, 1) + matrix(1, 2) + matrix(1, 3)) % MOD;
        }

        void merge(const Lazy &T) {
            this->matrix = this->matrix * T.matrix;
        }

        friend void Data::effect(const SegmentTree::Lazy &T);
    };
};