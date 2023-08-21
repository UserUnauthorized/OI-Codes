//Luogu - P5175
#include<bits/stdc++.h>

typedef long long valueType;

constexpr valueType MOD = 1e9 + 7;

class Matrix {
public:
    typedef long long valueType;
    typedef size_t sizeType;
    typedef std::vector<valueType> Row;
    typedef std::vector<Row> Container;

    enum TYPE : int {
        EMPTY = 0, UNIT = 1
    };

private:
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

    valueType &operator()(sizeType i, sizeType j) {
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
	valueType T;
	
	std::cin >> T;
	
	for(valueType i = 0; i < T; ++i) {
		valueType n, a1, a2, x, y;
		
		Matrix base(4, 4), ans(1, 4);
		
		std::cin >> n >> a1 >> a2 >> x >> y;
		
		if(n == 1) {
			std::cout << (a1 * a1) % MOD << '\n';
			
			continue;
		} else if(n == 2) {
			std::cout << (a1 * a1 + a2 * a2) % MOD << '\n';
			
			continue;
		}
		
		ans(1, 1) = a2 * a2 % MOD;
		ans(1, 2) = a1 * a1 % MOD;
		ans(1, 3) = a1 * a2 % MOD;
		ans(1, 4) = a1 * a1 % MOD;
		
		base(1, 1) = x * x % MOD;
		base(2, 1) = y * y % MOD;
		base(3, 1) = 2 * x * y % MOD;
		base(4, 1) = 0;
		
		base(1, 2) = 1;
		base(2, 2) = base(3, 2) = base(4, 2) = 0;
		
		base(1, 3) = x;
		base(3, 3) = y;
		base(2, 3) = base(4, 3) = 0;
		
		base(1, 4) = base(4, 4) = 1;
		base(2, 4) = base(3, 4) = 0;

		ans = ans * (base ^ (n - 1));
		
		std::cout << ans(1, 4) << '\n';
	}
	
	std::cout << std::flush;
	
	return 0;
}
