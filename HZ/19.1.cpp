//HZ - 19.1
//LOJ - 10219
#include<bits/stdc++.h>

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

class Maritx {
public:
    typedef int valueType;
    typedef size_t sizeType;
    typedef std::vector<valueType> Row;
    typedef std::vector<Row> Container;

public:
    sizeType row, column;
    Container data;

public:
    Maritx(sizeType _row_, sizeType _column_) : row(_row_), column(_column_), data(row + 1) {
        for (sizeType i = 1; i <= row; ++i)
            data[i].resize(column + 1, 0);
    };

    Maritx operator*(const Maritx &T) const {
        Maritx result(this->row, T.column);

        for (sizeType i = 1; i <= this->row; ++i) {
            for (sizeType k = 1; k <= this->column; ++k) {
                valueType r = this->data[i][k];

                for (sizeType j = 1; j <= T.column; ++j)
                    result.data[i][j] = result.data[i][j] + T.data[k][j] * r;
            }
        }

        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const Maritx &T) {
        for (sizeType i = 1; i <= T.row; ++i)
            for (sizeType j = 1; j <= T.column; ++j)
                os << T.data[i][j] << " \n"[j == T.column];

        return os;
    }

    friend std::istream &operator>>(std::istream &os, Maritx &T) {
        for (sizeType i = 1; i <= T.row; ++i)
            for (sizeType j = 1; j <= T.column; ++j)
                os >> T.data[i][j];

        return os;
    }
};

int main() {
    size_t n, m, p;

    std::cin >> n >> m;

    Maritx A(n, m);

    std::cin >> A;

    std::cin >> p;

    Maritx B(m, p);

    std::cin >> B;

    std::cout << (A * B) << std::flush;

    return 0;
}
