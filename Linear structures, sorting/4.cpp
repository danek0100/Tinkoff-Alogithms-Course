/* Кошмар в замке
Формат входных данных
Дана строка, состоящая из строчных букв латинского алфавита (1≤|s|≤10^5). 
Следующая строка ввода содержит 26 чисел — веса букв латинского алфавита от «a» до «z», веса неотрицательны и не превосходят 2^31−1.

Формат результата
Выведите строку s, в которой переставлены буквы так, чтобы полученный вес был максимально возможным.
 Если искомых вариантов несколько, выведите любой из них. */


#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <ostream>
#include <iomanip>
#include <sstream>

class big_integer {
    // ��������� ������� ��������� (1 000 000 000)
    static const int BASE = 1000000000;

    // ���������� ��������� �����
    std::vector<int> _digits;

    // ���� �����
    bool _is_negative;

    void _remove_leading_zeros();
    void _shift_right();

public:
    // �����-����������, ��������� ��� ������� �� ����
    class divide_by_zero : public std::exception {  };

    big_integer();
    big_integer(std::string);
    big_integer(signed char);
    big_integer(unsigned char);
    big_integer(signed short);
    big_integer(unsigned short);
    big_integer(signed int);
    big_integer(unsigned int);
    big_integer(signed long);
    big_integer(unsigned long);
    big_integer(signed long long);
    big_integer(unsigned long long);

    friend std::ostream& operator <<(std::ostream&, const big_integer&);
    operator std::string() const;
    const big_integer operator +() const;
    const big_integer operator -() const;
    const big_integer operator ++();
    const big_integer operator ++(int);
    const big_integer operator --();
    const big_integer operator --(int);
    friend bool operator ==(const big_integer&, const big_integer&);
    friend bool operator <(const big_integer&, const big_integer&);
    friend bool operator !=(const big_integer&, const big_integer&);
    friend bool operator <=(const big_integer&, const big_integer&);
    friend bool operator >(const big_integer&, const big_integer&);
    friend bool operator >=(const big_integer&, const big_integer&);
    friend const big_integer operator +(big_integer, const big_integer&);
    big_integer& operator +=(const big_integer&);
    friend const big_integer operator -(big_integer, const big_integer&);
    big_integer& operator -=(const big_integer&);
    friend const big_integer operator *(const big_integer&, const big_integer&);
    big_integer& operator *=(const big_integer&);
    friend const big_integer operator /(const big_integer&, const big_integer&);
    big_integer& operator /=(const big_integer&);
    friend const big_integer operator %(const big_integer&, const big_integer&);
    big_integer& operator %=(const big_integer&);

    bool odd() const;
    bool even() const;
    const big_integer pow(big_integer) const;
};

// ������� ������� ����� ����� �� ��������� 0
big_integer::big_integer() {
    this->_is_negative = false;
}

// ������� ������� ����� ����� �� C++-������
big_integer::big_integer(std::string str) {
    if (str.length() == 0) {
        this->_is_negative = false;
    }
    else {
        if (str[0] == '-') {
            str = str.substr(1);
            this->_is_negative = true;
        }
        else {
            this->_is_negative = false;
        }

        for (long long i = str.length(); i > 0; i -= 9) {
            if (i < 9)
                this->_digits.push_back(atoi(str.substr(0, i).c_str()));
            else
                this->_digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
        }

        this->_remove_leading_zeros();
    }
}

// ������� ������� ����
void big_integer::_remove_leading_zeros() {
    while (this->_digits.size() > 1 && this->_digits.back() == 0) {
        this->_digits.pop_back();
    }

    if (this->_digits.size() == 1 && this->_digits[0] == 0) this->_is_negative = false;
}

// �������� ����� � ����� ������
std::ostream& operator <<(std::ostream& os, const big_integer& bi) {
    if (bi._digits.empty()) os << 0;
    else {
        if (bi._is_negative) os << '-';
        os << bi._digits.back();
        char old_fill = os.fill('0');
        for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i) os << std::setw(9) << bi._digits[i];
        os.fill(old_fill);
    }

    return os;
}

// ���������� ��� ����� �� ���������
bool operator ==(const big_integer& left, const big_integer& right) {
    if (left._is_negative != right._is_negative) return false;
    if (left._digits.empty()) {
        if (right._digits.empty() || (right._digits.size() == 1 && right._digits[0] == 0)) return true;
        else return false;
    }

    if (right._digits.empty()) {
        if (left._digits.size() == 1 && left._digits[0] == 0) return true;
        else return false;
    }

    if (left._digits.size() != right._digits.size()) return false;
    for (size_t i = 0; i < left._digits.size(); ++i) if (left._digits[i] != right._digits[i]) return false;

    return true;
}

// ���������� ����� ����������� �����
const big_integer big_integer::operator +() const {
    return big_integer(*this);
}

// ���������� ���������� ����� � ������ ������
const big_integer big_integer::operator -() const {
    big_integer copy(*this);
    copy._is_negative = !copy._is_negative;
    return copy;
}

// ���������, �������� �� ����� ������� ������ �������
bool operator <(const big_integer& left, const big_integer& right) {
    if (left == right) return false;
    if (left._is_negative) {
        if (right._is_negative) return ((-right) < (-left));
        else return true;
    }
    else if (right._is_negative) return false;
    else {
        if (left._digits.size() != right._digits.size()) {
            return left._digits.size() < right._digits.size();
        }
        else {
            for (long long i = left._digits.size() - 1; i >= 0; --i) {
                if (left._digits[i] != right._digits[i]) return left._digits[i] < right._digits[i];
            }

            return false;
        }
    }
}

// ���������� ��� ����� �� �����������
bool operator !=(const big_integer& left, const big_integer& right) {
    return !(left == right);
}

// ���������, �������� �� ����� ������� ������ ���� ����� �������
bool operator <=(const big_integer& left, const big_integer& right) {
    return (left < right || left == right);
}

// ���������, �������� �� ����� ������� ������ �������
bool operator >(const big_integer& left, const big_integer& right) {
    return !(left <= right);
}

// ���������, �������� �� ����� ������� ������ ���� ����� �������
bool operator >=(const big_integer& left, const big_integer& right) {
    return !(left < right);
}

// ���������� ��� �����
const big_integer operator +(big_integer left, const big_integer& right) {
    if (left._is_negative) {
        if (right._is_negative) return -(-left + (-right));
        else return right - (-left);
    }
    else if (right._is_negative) return left - (-right);
    int carry = 0;
    for (size_t i = 0; i < std::max(left._digits.size(), right._digits.size()) || carry != 0; ++i) {
        if (i == left._digits.size()) left._digits.push_back(0);
        left._digits[i] += carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] >= big_integer::BASE;
        if (carry != 0) left._digits[i] -= big_integer::BASE;
    }

    return left;
}

// ���������� � �������� ����� �����
big_integer& big_integer::operator +=(const big_integer& value) {
    return *this = (*this + value);
}

// ���������� ���������
const big_integer big_integer::operator++() {
    return (*this += 1);
}

// ����������� ����� � ������
big_integer::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

// ����������� signed char � big_integer
big_integer::big_integer(signed char c) {
    if (c < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(c));
}

// ����������� unsigned char � big_integer
big_integer::big_integer(unsigned char c) {
    this->_is_negative = false;
    this->_digits.push_back(c);
}

// ����������� signed short � big_integer
big_integer::big_integer(signed short s) {
    if (s < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(s));
}

// ����������� unsigned short � big_integer
big_integer::big_integer(unsigned short s) {
    this->_is_negative = false;
    this->_digits.push_back(s);
}

// ����������� signed int � big_integer
big_integer::big_integer(signed int i) {
    if (i < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(i) % big_integer::BASE);
    i /= big_integer::BASE;
    if (i != 0) this->_digits.push_back(std::abs(i));
}

// ����������� unsigned int � big_integer
big_integer::big_integer(unsigned int i) {
    this->_digits.push_back(i % big_integer::BASE);
    i /= big_integer::BASE;
    if (i != 0) this->_digits.push_back(i);
}

// ����������� signed long � big_integer
big_integer::big_integer(signed long l) {
    if (l < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(l) % big_integer::BASE);
    l /= big_integer::BASE;
    if (l != 0) this->_digits.push_back(std::abs(l));
}

// ����������� unsigned long � big_integer
big_integer::big_integer(unsigned long l) {
    this->_digits.push_back(l % big_integer::BASE);
    l /= big_integer::BASE;
    if (l != 0) this->_digits.push_back(l);
}

// ����������� signed long long � big_integer
big_integer::big_integer(signed long long l) {
    if (l < 0) { this->_is_negative = true; l = -l; }
    else this->_is_negative = false;
    do {
        this->_digits.push_back(l % big_integer::BASE);
        l /= big_integer::BASE;
    } while (l != 0);
}

// ����������� unsigned long long � big_integer
big_integer::big_integer(unsigned long long l) {
    this->_is_negative = false;
    do {
        this->_digits.push_back(l % big_integer::BASE);
        l /= big_integer::BASE;
    } while (l != 0);
}

// ����������� ���������
const big_integer big_integer::operator ++(int) {
    *this += 1;
    return *this - 1;
}

// ���������� ���������
const big_integer big_integer::operator --() {
    return *this -= 1;
}

// ����������� ���������
const big_integer big_integer::operator --(int) {
    *this -= 1;
    return *this + 1;
}

// �������� ��� �����
const big_integer operator -(big_integer left, const big_integer& right) {
    if (right._is_negative) return left + (-right);
    else if (left._is_negative) return -(-left + right);
    else if (left < right) return -(right - left);
    int carry = 0;
    for (size_t i = 0; i < right._digits.size() || carry != 0; ++i) {
        left._digits[i] -= carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] < 0;
        if (carry != 0) left._digits[i] += big_integer::BASE;
    }

    left._remove_leading_zeros();
    return left;
}

// �������� �� �������� ����� �����
big_integer& big_integer::operator -=(const big_integer& value) {
    return *this = (*this - value);
}

// ����������� ��� �����
const big_integer operator *(const big_integer& left, const big_integer& right) {
    big_integer result;
    result._digits.resize(left._digits.size() + right._digits.size());
    for (size_t i = 0; i < left._digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right._digits.size() || carry != 0; ++j) {
            long long cur = result._digits[i + j] +
                left._digits[i] * 1LL * (j < right._digits.size() ? right._digits[j] : 0) + carry;
            result._digits[i + j] = static_cast<int>(cur % big_integer::BASE);
            carry = static_cast<int>(cur / big_integer::BASE);
        }
    }

    result._is_negative = left._is_negative != right._is_negative;
    result._remove_leading_zeros();
    return result;
}

// ��������� ������� ����� �� ���������
big_integer& big_integer::operator *=(const big_integer& value) {
    return *this = (*this * value);
}

// �������� ��� ������� �� 1 ������ (��������� �� BASE)
void big_integer::_shift_right() {
    if (this->_digits.size() == 0) {
        this->_digits.push_back(0);
        return;
    }
    this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
    for (size_t i = this->_digits.size() - 2; i > 0; --i) this->_digits[i] = this->_digits[i - 1];
    this->_digits[0] = 0;
}

// ����� ��� �����
const big_integer operator /(const big_integer& left, const big_integer& right) {
    if (right == 0) throw big_integer::divide_by_zero();
    big_integer b = right;
    b._is_negative = false;
    big_integer result, current;
    result._digits.resize(left._digits.size());
    for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0; --i) {
        current._shift_right();
        current._digits[0] = left._digits[i];
        current._remove_leading_zeros();
        int x = 0, l = 0, r = big_integer::BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            big_integer t = b * m;
            if (t <= current) {
                x = m;
                l = m + 1;
            }
            else r = m - 1;
        }

        result._digits[i] = x;
        current = current - b * x;
    }

    result._is_negative = left._is_negative != right._is_negative;
    result._remove_leading_zeros();
    return result;
}

// ����� ������� ����� �� ���������
big_integer& big_integer::operator /=(const big_integer& value) {
    return *this = (*this / value);
}

// ���������� ������� �� ������� ���� �����
const big_integer operator %(const big_integer& left, const big_integer& right) {
    big_integer result = left - (left / right) * right;
    if (result._is_negative) result += right;
    return result;
}

// ����������� �������� ����� ������� �� ������� �� ������ �����
big_integer& big_integer::operator %=(const big_integer& value) {
    return *this = (*this % value);
}

// ���������, �������� �� ������� ����� ��������
bool big_integer::odd() const {
    if (this->_digits.size() == 0) return false;
    return this->_digits[0] & 1;
}

// ���������, �������� �� ������� ����� ������
bool big_integer::even() const {
    return !this->odd();
}

// �������� ������� ����� � ��������� �������
const big_integer big_integer::pow(big_integer n) const {
    big_integer a(*this), result(1);
    while (n != 0) {
        if (n.odd()) result *= a;
        a *= a;
        n /= 2;
    }

    return result;
}

bool comp(std::pair<char, big_integer> a, std::pair<char, big_integer> b) {
	return a.second > b.second;
}

int main() {
	std::string word;
	std::cin >> word;
    big_integer* prices = new big_integer[26];
    std::string number;
	for (int i = 0; i < 26; i++) {
		std::cin >> number;
        prices[i] = number;
	}
	std::vector<std::pair<char, big_integer>> pair_price;
	long long m[26] = { 0 };

	for (int i = 0; i < word.length(); i++) {
		std::pair<char, big_integer> myPair(word[i], prices[word[i] - 'a']);
		m[word[i] - 'a']++;
		pair_price.push_back(myPair);
	}

	std::sort(pair_price.begin(), pair_price.end(), comp);
	long long free_index = 0;
	for (long long i = 0; i < word.length(); i++) {
		if (m[pair_price[i].first - 'a'] > 1) {
			if (i != free_index) {
				std::swap(pair_price[i], pair_price[free_index]);
			}
			for (long long j = free_index + 1; j < word.length(); j++) {
				if (pair_price[free_index].first == pair_price[j].first) {
					if (j != pair_price.size() - 1 - free_index) {
						std::swap(pair_price[j], pair_price[pair_price.size() - 1 - free_index ]);
						break;
					}
				}
			}
			m[pair_price[free_index].first - 'a'] = 1;
			free_index++;
            std::sort(pair_price.begin()+free_index, pair_price.end()-free_index, comp);
		}

		
	}

	for (int i = 0; i < word.length(); i++) {
		std::cout << pair_price[i].first;
	}

	delete[] prices;
}