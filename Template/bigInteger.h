#ifndef OI_CODES_BIGINTEGER_H
#define OI_CODES_BIGINTEGER_H

#include <iostream>
#include <vector>
#include <algorithm>

class bigInteger {

    /**@brief BigInteger class used for OI.
     * @author User-Unauthorized
     * @version 1.2.1*/

#define OI_CODES_BIGINTEGER_H_DECIMAL true

public:
#ifdef OI_CODES_BIGINTEGER_H_DECIMAL
    /**@brief Decimal mode.*/
    typedef int value_type;
    const static value_type base = 10;
    //TODO: add other mode
#endif

public:
    typedef std::vector<value_type> container_type;
    typedef container_type::iterator iterator;
    typedef container_type::const_iterator const_iterator;
    typedef container_type::reverse_iterator reverse_iterator;
    typedef container_type::const_reverse_iterator const_reverse_iterator;
    typedef container_type::reference reference;
    typedef container_type::const_reference const_reference;
    typedef container_type::size_type size_type;
    typedef container_type::difference_type difference_type;

private:
    container_type _number_;
    bool _positive_;

public:
    /**@brief Default constructor.*/
    bigInteger() : _number_(0), _positive_(true) {}

    /**@brief Construct a bigInteger from a int.
     * @param x the int*/
    template<class T>
    explicit bigInteger(T x) : _positive_(true) {
        if (x < 0) {
            x = -x;
            _positive_ = false;
        }
        for (; x; x /= bigInteger::base) {
            _number_.push_back(x % bigInteger::base);
        }
    }

    ~bigInteger() = default;

    bigInteger(const bigInteger &other) = default;

    bigInteger(bigInteger &&other) noexcept = default;

    bigInteger &operator=(const bigInteger &other) = default;

    bigInteger &operator=(bigInteger &&other) noexcept = default;

    /**@brief Scan a bigInteger from stdin.*/
    void scan() {
        int ch(getchar());
        while (ch != '-' && (ch < '0' || ch > '9'))
            ch = getchar();
        if (ch == '-') {
            this->_positive_ = false;
            ch = getchar();
        } else this->_positive_ = true;
        while (ch >= '0' && ch <= '9') {
            this->_number_.push_back(ch - '0');
            ch = getchar();
        }
        std::reverse(this->_number_.begin(), this->_number_.end());
    }

    /**@brief Print a bigInteger to stdout.*/
    void put() const {
        if (this->_number_.empty()) {
            std::cout << 0;
            return;
        }
        if (!this->_positive_)
            putchar('-');
        for (auto iter = this->_number_.rbegin(); iter != this->_number_.rend(); ++iter)
            std::cout << *iter;
    }

    /**@brief Overload output operator.*/
    friend std::ostream &operator<<(std::ostream &output, const bigInteger &Object) {
        if (Object._number_.empty()) {
            output << 0;
            return output;
        }
        if (!Object._positive_)
            output << '-';
        for (auto iter = Object._number_.rbegin(); iter != Object._number_.rend(); ++iter)
            output << *iter;
        return output;
    }

    /**@brief Overload input operator.*/
    friend std::istream &operator>>(std::istream &input, bigInteger &Object) {
        char ch(0);
        while ((input >> std::noskipws >> ch) && ch != '-' && (ch < '0' || ch > '9'));
        if (ch == '-') {
            Object._positive_ = false;
            input >> std::noskipws >> ch;
        } else Object._positive_ = true;
        do {
            Object._number_.push_back(ch - '0');
        } while ((input >> std::noskipws >> ch) && ch >= '0' && ch <= '9');
        std::reverse(Object._number_.begin(), Object._number_.end());
        return input;
    }

    /**@brief Carry the bigInteger.*/
    void carry() {
        while (!_number_.empty() && _number_.back() == 0)
            _number_.pop_back();
        if (_number_.empty())
            return;
        auto iter = _number_.begin();
        for (; next(iter) != _number_.end(); ++iter) {
            std::vector<int>::iterator nextIter;
            nextIter = std::next(iter);
            if (*iter < 0) {
                *nextIter += *iter / base - 1;
                *iter = (*iter % base + base) % base;
            } else if (*iter >= base) {
                *nextIter += *iter / base;
                *iter %= base;
            }
        }
        if (*iter < 0) {
            for (int &it: _number_)
                it = -it;
            _positive_ = !_positive_;
            carry();
        }
        while (*iter >= base) {
            int const it = *iter;
            *iter %= base;
            iter = _number_.insert(next(iter), it / base);
        }
        while (!_number_.empty() && _number_.back() == 0)
            _number_.pop_back();
    }

private:
    /**@brief Add only digits (sign and carry are ignored).*/
    bigInteger _addition_(const bigInteger &Object) const {
        bigInteger result;
        result._positive_ = this->_positive_;
        result._number_.resize(std::max(this->_number_.size(), Object._number_.size()), 0);
        for (size_t i = 0; i < result._number_.size(); ++i) {
            if (i < this->_number_.size())
                result._number_[i] += this->_number_[i];
            if (i < Object._number_.size())
                result._number_[i] += Object._number_[i];
        }
        return result;
    }

	/**@brief Sub only digits (sign and carry are ignored).*/
    bigInteger _subtraction_(const bigInteger &Object) const {
        bigInteger result;
        result._positive_ = this->_positive_;
        result._number_.resize(std::max(this->_number_.size(), Object._number_.size()), 0);
        for (size_t i = 0; i < result._number_.size(); ++i) {
            if (i < this->_number_.size())
                result._number_[i] += this->_number_[i];
            if (i < Object._number_.size())
                result._number_[i] -= Object._number_[i];
        }
        return result;
    }

    /**@brief Multiply only digits (carry is ignored).*/
    bigInteger _multiplication_(const bigInteger &Object) const {
        bigInteger result;
        result._positive_ = this->_positive_ == Object._positive_;
        result._number_.resize(this->_number_.size() + Object._number_.size(), 0);
        for (size_t i = 0; i < this->_number_.size(); ++i) {
            for (size_t j = 0; j < Object._number_.size(); ++j) {
                result._number_[i + j] += this->_number_[i] * Object._number_[j];
            }
        }
        return result;
    }

    /**@brief Multiply only digits (carry is ignored).*/
    template<class T>
    bigInteger _multiplication_(const T &n) const {
        bigInteger result = *this;
        for (auto &iter: result._number_)
            iter = iter * n;
        return result;
    }

    /**@brief Intercept the number at the specified position and the specified length in the number
     * @param pos The position of the number to intercept
     * @param len The length of the number to intercept*/
    bigInteger _intercept_(const difference_type pos, difference_type len) const {
        bigInteger result;
        result._positive_ = this->_positive_;
        result._number_.assign(this->_number_.begin() + pos, this->_number_.begin() + pos + len);
        return result;
    }

	/**@brief intercepts the number at the specified position
     * @param first An input iterator.
     * @param last An input iterator.
     * @warning The input interval is processed according to A right half-open interval*/
    bigInteger _intercept_(iterator first, iterator last) const {
        return this->_intercept_(first - this->_number_.begin(), last - first);
    }

    /**@brief Start doing subtraction at a certain part of the number(carry is ignored).
     * @param start The position of the number to start subtracting
     * @param left minuend
     * @param right subtrahend*/
    static void _partial_subtraction_(bigInteger &left, const bigInteger &right, size_type start) {
        for (int i = 0; i < right._number_.size(); ++i)
            left._number_[i + start] -= right._number_[i];
    }

    /**@brief Divide only digits (carry is ignored).*/
    bigInteger _division_(const bigInteger &Object) const {
        if (this->_number_.size() < Object._number_.size())
            return bigInteger(0);
        bigInteger result;
        bigInteger divisor = Object;
        divisor._positive_ = true;
        bigInteger dividend = *this;
        dividend._positive_ = true;
        result._positive_ = this->_positive_ == divisor._positive_;
        result._number_.resize(this->_number_.size() - divisor._number_.size() + 1, 0);
        for (int i = (int) dividend._number_.size() - 1; i >= 0; --i) {
            while (dividend._intercept_(dividend._number_.begin() + i, dividend._number_.end()) >= divisor) {
                bigInteger::_partial_subtraction_(dividend, divisor, i);
                dividend.carry();
                ++result._number_[i];
            }
        }
        return result;
    }

public:
    /**@brief Overload operator +*/
    bigInteger operator+(const bigInteger &Object) const {
        bigInteger result;
        if (this->_positive_ != Object._positive_)
            result = this->_subtraction_(Object);
        else
            result = this->_addition_(Object);
        result.carry();
        return result;
    }

    /**@brief Overload operator -*/
    bigInteger operator-(const bigInteger &Object) const {
        bigInteger result;
        if (this->_positive_ != Object._positive_)
            result = this->_addition_(Object);
        else
            result = this->_subtraction_(Object);
        result.carry();
        return result;
    }

    /**@brief Generalize the operator -*/
    template<class T>
    bigInteger operator-(const T &Object) const {
        bigInteger result;
        result = *this - bigInteger(Object);
        result.carry();
        return result;
    }

    /**@brief Overload operator * */
    bigInteger operator*(const bigInteger &Object) const {
        bigInteger result;
        result = this->_multiplication_(Object);
        result.carry();
        return result;
    }

    /**@brief Generalize the operator * */
    template<class T>
    bigInteger operator*(const T &Object) const {
        bigInteger result;
        result = this->_multiplication_(bigInteger(Object));
        result.carry();
        return result;
    }

    /**@brief Overload operator / */
    bigInteger operator/(const bigInteger &Object) const {
        bigInteger result;
        result = this->_division_(Object);
        result.carry();
        return result;
    }

    /**@brief Generalize the operator \< */
    bool operator<(const bigInteger &Object) const {
        if (this->_positive_ != Object._positive_)
            return (this->_positive_ < Object._positive_);
        if (this->_number_.size() != Object._number_.size())
            return (this->_number_.size() < Object._number_.size()) ^ !this->_positive_;

        auto this_iter = this->_number_.rbegin();
        auto Object_iter = Object._number_.rbegin();
        for (; this_iter != this->_number_.rend(); ++this_iter, ++Object_iter)
            if (*this_iter != *Object_iter)
                return (*this_iter < *Object_iter) ^ !this->_positive_;

        return false;
    }

    /**@brief Generalize the operator > */
    bool operator>(const bigInteger &Object) const {
        if (this->_positive_ != Object._positive_)
            return (this->_positive_ > Object._positive_);
        if (this->_number_.size() != Object._number_.size())
            return (this->_number_.size() > Object._number_.size()) ^ !this->_positive_;

        auto this_iter = this->_number_.rbegin();
        auto Object_iter = Object._number_.rbegin();
        for (; this_iter != this->_number_.rend(); ++this_iter, ++Object_iter)
            if (*this_iter != *Object_iter)
                return (*this_iter > *Object_iter) ^ !this->_positive_;

        return false;
    }

    /**@brief Generalize the operator <= */
    bool operator==(const bigInteger &Object) const {
        if (this->_positive_ != Object._positive_ || this->_number_.size() != Object._number_.size())
            return false;

        auto this_iter = this->_number_.rbegin();
        auto Object_iter = Object._number_.rbegin();
        for (; this_iter != this->_number_.rend(); ++this_iter, ++Object_iter)
            if (*this_iter != *Object_iter)
                return false;

        return true;
    }

    /**@brief Generalize the operator != */
    bool operator!=(const bigInteger &Object) const {
        return !(*this == Object);
    }

    /**@brief Generalize the operator <= */
    void operator+=(const bigInteger &Object) {
        *this = *this + Object;
    }

    /**@brief Generalize the operator -= */
    void operator-=(const bigInteger &Object) {
        *this = *this - Object;
    }

    /**@brief Generalize the operator *= */
    void operator*=(const bigInteger &Object) {
        *this = *this * Object;
    }

    /**@brief Generalize the operator /= */
    void operator/=(const bigInteger &Object) {
        *this = *this / Object;
    }

    /**@brief Generalize the operator \<= */
    bool operator<=(const bigInteger &Object) const {
        return !(*this > Object);
    }

    /**@brief Generalize the operator >= */
    bool operator>=(const bigInteger &Object) const {
        return !(*this < Object);
    }

    /**@brief Overload operator ++ */
    bigInteger operator++() {
        auto iter = this->_number_.begin();
        do {
            ++(*iter);
            if (*iter >= bigInteger::base) {
                *iter = 0;
                ++iter;
            } else {
                break;
            }
        } while (iter != this->_number_.end());
        if (iter == this->_number_.end())
            this->_number_.push_back(1);

        return *this;
    }

    /**@brief Overload operator -- */
    bigInteger operator--() {
        auto iter = this->_number_.begin();
        do {
            --(*iter);
            if (*iter < 0) {
                *iter = bigInteger::base - 1;
                ++iter;
            } else {
                break;
            }
        } while (iter != this->_number_.end());
        if (iter == this->_number_.end())
            this->_number_.push_back(1);

        return *this;
    }

    /**@brief Get the factorial of the int*/
    bigInteger factorial() const {
        bigInteger result(1);
        int count(1);
        for (bigInteger i(2); i <= *this; ++i, ++count) {
            result = result._multiplication_(i);
            if (count & 3) {
                count = 0;
                result.carry();
            }
        }
        result.carry();
        return result;
    }

	template<typename T>
	friend bigInteger factorial(std::vector<T> _factors_);
    friend bigInteger factorial(int _n_);

    explicit operator bool() const {
        return *this != bigInteger(0);
    }
};

template<typename T>
bigInteger factorial(std::vector<T> _factors_){
	bigInteger result(1);
	const int _size_ = _factors_.size();
	int _count_ = 0;
	for(int i = 2; i < _size_; ++i){
		while(_factors_[i]--){
			result = result._multiplication_(i);
			++_count_;
			if(_count_ & 1)
				result.carry();
		}
	}
	return result;
}

bigInteger factorial(int _n_) {
    bigInteger result(1);
    for (int i = 2; i <= _n_; ++i) {
        result = result._multiplication_(i);
        if (i & 1)
            result.carry();
    }
    result.carry();
    return result;
}


#endif //OI_CODES_BIGINTEGER_H
