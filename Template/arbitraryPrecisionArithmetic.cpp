//arbitraryPrecisionArithmetic
#include <bits/stdc++.h>

using namespace std;

class bigNum {
public:
    vector<int> number;
    bool positive;

    bigNum() {
        positive = true;
    }


    bigNum(int x) {
        if (x < 0)x = -x, positive = false;
        for (; x; x /= 10)
            number.push_back(x % 10);
    }

    bigNum(long long x) {
        if (x < 0)x = -x, positive = false;
        for (; x; x /= 10)
            number.push_back(x % 10);
    }

    bigNum(unsigned int x) {
        for (; x; x /= 10)
            number.push_back(x % 10);
    }

    bigNum(unsigned long long x) {
        for (; x; x /= 10)
            number.push_back(x % 10);
    }


    void scan() {
        char ch = getchar();
        while (ch != '-' && (ch < '0' || ch > '9'))
            ch = getchar();
        if (ch == '-') {
            positive = false;
            ch = getchar();
        } else positive = true;
        while (ch >= '0' && ch <= '9') {
            number.push_back(ch - '0');
            ch = getchar();
        }
        reverse(number.begin(), number.end());
        return;
    }

    void put() {
        if (number.empty()) {
            printf("%d", 0);
            return;
        }
        if (!positive)
            putchar('-');
        for (auto iter = number.rbegin(); iter != number.rend(); ++iter)
            printf("%d", *iter);
        return;
    }

    void carry() {
        while (number.size() && number.back() == 0)
            number.pop_back();
        if (number.empty())
            return;
        auto iter = number.begin();
        for (; next(iter) != number.end(); ++iter) {
            vector<int>::iterator nextIter;
            nextIter = std::next(iter);
            if (*iter < 0) {
                --*nextIter;
                *iter += 10;
            } else if (*iter > 9) {
                *nextIter += *iter / 10;
                *iter %= 10;
            }
        }
        if (*iter < 0) {
            for (auto it = number.begin(); it != number.end(); ++it)
                *it = -*it;
            positive = !positive;
            carry();
        }
        while (*iter > 9) {
            int it = *iter;
            *iter %= 10;
            iter = number.insert(next(iter), it / 10);
        }
        while (number.size() && number.back() == 0)
            number.pop_back();
        return;
    }

    void operator=(const bigNum &other) {
        number = other.number;
        positive = other.positive;
    }

    bigNum operator+(bigNum other) const {
        if (this->positive != other.positive) {
            other.positive = !other.positive;
            return *this - other;
        }
        other.number.resize(max(other.number.size(), this->number.size()), 0);
        //number.resize(max(other.number.size(), this->number.size()), 0);
        for (int i = 0; i < this->number.size(); ++i)
            other.number[i] += this->number[i];
        other.carry();
        return other;
    }

    bigNum operator-(bigNum other) const {
        if (this->positive != other.positive) {
            other.positive = !other.positive;
            return *this + other;
        }
        bigNum temp = *this, result;
        result.positive = this->positive;
        other.number.resize(max(other.number.size(), this->number.size()), 0);
        temp.number.resize(other.number.size(), 0);
        result.number.resize(other.number.size(), 0);
        for (int i = 0; i < temp.number.size(); ++i)
            result.number[i] = temp.number[i] - other.number[i];
        result.carry();
        return result;
    }

    bigNum operator*(bigNum other) const {
        bigNum result;
        result.positive = (other.positive == this->positive);
        result.number.resize(this->number.size() + other.number.size());
        for (int i = 0; i < this->number.size(); ++i)
            for (int j = 0; j < other.number.size(); ++j)
                result.number[i + j] += this->number[i] * other.number[j];
        result.carry();
        return result;
    }

    bigNum operator/(bigNum other) {
        if (this->number.size() < other.number.size())
            return bigNum(0);
        bigNum result, temp;
        temp = *this;
        result.positive = (other.positive == this->positive);
        temp.positive = other.positive = true;
        result.number.resize(this->number.size() - other.number.size() + 1);
        for (int i = temp.number.size() - 1; i >= 0; --i) {
            while (getSubNum(temp, i, temp.number.size() - 1) >= other) {
                subtraction(temp, other, i);
                ++result.number[i];
            }
        }
        result.carry();
        return result;
    }

    bool operator<(bigNum other) {
        if (this->positive != other.positive)
            return (this->positive < other.positive);
        if (this->number.size() != other.number.size()) {
            if (this->positive)
                return (this->number.size() < other.number.size());
            else
                return (this->number.size() > other.number.size());
        }
        for (int i = this->number.size() - 1; i >= 0; --i)
            if (this->number[i] != other.number[i])
                if (this->positive)
                    return (this->number[i] < other.number[i]);
                else
                    return (this->number[i] > other.number[i]);
        return false;
    }

    bool operator>(bigNum other) {
        if (this->positive != other.positive)
            return (this->positive > other.positive);
        if (this->number.size() != other.number.size()) {
            if (this->positive)
                return (this->number.size() > other.number.size());
            else
                return (this->number.size() < other.number.size());
        }
        for (int i = this->number.size() - 1; i >= 0; --i)
            if (this->number[i] != other.number[i])
                if (this->positive)
                    return (this->number[i] > other.number[i]);
                else
                    return (this->number[i] < other.number[i]);
        return false;
    }

    bool operator==(bigNum other) {
        if (this->positive != other.positive || this->number.size() != other.number.size())
            return false;
        for (int i = this->number.size() - 1; i >= 0; --i)
            if (this->number[i] != other.number[i])
                return false;
        return true;
    }

    void operator+=(bigNum other) {
        *this = *this + other;
        this->carry();
        return;
    }

    void operator-=(bigNum other) {
        *this = *this - other;
        this->carry();
        return;
    }

    void operator*=(bigNum other) {
        *this = *this * other;
        this->carry();
        return;
    }

    void operator/=(bigNum other) {
        *this = *this / other;
        this->carry();
        return;
    }

    bool operator<=(bigNum other) {
        return (*this < other || *this == other);
    }

    bool operator>=(bigNum other) {
        return (*this > other || *this == other);
    }

    friend bigNum max(bigNum a, bigNum b) {
        if (a > b)return a;
        else return b;
    }

    friend bigNum min(bigNum a, bigNum b) {
        if (a < b)return a;
        else return b;
    }

private:
    bigNum getSubNum(const bigNum &temp, const int &l, const int &r) {
        bigNum result;
        result.positive = temp.positive;
        for (int i = l; i <= r; ++i)
            result.number.push_back(temp.number[i]);
        return result;
    }

    void subtraction(bigNum &temp, const bigNum &other, const int &t) {
        for (int i = 0; i < other.number.size(); ++i)
            temp.number[i + t] -= other.number[i];
        temp.carry();
    }
};

int main() {
    bigNum a, b;
    a.scan();
    b.scan();
    (a + b).put();
    return 0;
}
