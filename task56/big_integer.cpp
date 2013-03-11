#include "big_integer.h"
	
using namespace std;

const unsigned sz = 32;

int compare(big_integer const& a, big_integer const& b) {
	if (a.sign == 0 && a.sign) return 1; // a > b
	if (a.sign && b.sign == 0) return -1; // a < b
	size_t max_len = max(a.data.size(), b.data.size());
	unsigned c1, c2;
	// inv: a.sign == b.sign 
	for (size_t i = max_len - 1; i >= 0; --i) {
		c1 = (i < a.data.size() ? a.data.get(i) : a.sign);
		c2 = (i < b.data.size() ? b.data.get(i) : b.sign);
		if (c1 < c2) return -1;
		if (c1 > c2) return 1;

		if (i == 0) break; // не знаю как еще сделать, используя size_t
	}
	return 0;
}

void big_integer::change() {
	if (sign) {
		for (size_t i = 0; i < data.size(); ++i) {
			data.set(i, ~data.get(i));
		}
		for (size_t i = 0; i < data.size(); ++i) {
			unsigned res = data.get(i) + 1;
			data.set(i, res);
			if (!(res < 1)) break; // проверка на переполнение разряда
		}
	}
	normalize();
}

big_integer& big_integer::normalize() {
	while(data.size() > 1 && data.back() == sign)
		data.pop_back();
	return *this;
}

unsigned big_integer::get_bit(unsigned i) {
	unsigned block = i / sz;
	i %= sz;
	return (data.get(block) & (1 << i) ? 1 : 0);

	if (block < data.size()) {
		return (data.get(block) & (1 << i) ? 1 : 0);
	} else
	{
		return (sign ? 1 : 0);
	}
}

void big_integer::set_bit(unsigned i, unsigned x) {
	unsigned block = i / sz;
	i %= sz;
	
	if (x) {
		data.set(block, data.get(block) | (1 << i));
	} else
	{
		unsigned t = 1;
		t = t << i;
		t = ~t;
		data.set(block, data.get(block) & t);
	}
}

unsigned big_integer::get_block(int i) {
	int pos_arr = i / sz;
	int pos_num = i % sz;

	unsigned x1 = data.get(pos_arr);
	if (pos_num == 0) return x1;

	unsigned mask1 = 0; mask1 = ~mask1; // 1111
	mask1 <<= (sz - pos_num); // 1000
	mask1 = ~mask1; // 0111
	x1 = x1 & mask1; // 0xyz. х,y,z - какие-то биты

	//if (pos_arr == v.size() - 1) return x1; // следующий блок уже пуст
	x1 <<= (pos_num); //xyz0. потом к нему что-нибудь прибавим

	unsigned x2 = data.get(pos_arr + 1);
	// нужные биты сдвинем вправо
	x2 >>= (sz - pos_num); // 111t 
	unsigned mask2 = 0; mask2 = ~mask2; // 1111
	mask2 <<= pos_num; // 1110
	mask2 = ~mask2; // 0001
	x2 = x2 & mask2; // 000t
	return x1 + x2;
}

void big_integer::set_block(int i, unsigned value) {
	int pos_arr = i / sz;
	int pos_num = i % sz;

	if (pos_num == 0) {
		data.set(pos_arr, value);
	} else
	{
		// перезапишем первый блок
		unsigned x = data.get(pos_arr);

		// заготовим место
		unsigned mask = 0; mask = ~mask;
		mask <<= (sz - pos_num);
		x = x & mask; // ???00
		// заготовим кусок для записи
		unsigned long long t = value;
		t >>= pos_num; // 000xy
		data.set(pos_arr, (unsigned)(x + t));

		// перезапишем второй блок
		x = data.get(pos_arr + 1);

		// заготовим место
		mask = 0; mask = ~mask;
		unsigned long long mask2 = mask;
		mask2 >>= pos_num; // 000???
		x = x & mask2;
		value <<= (sz - pos_num);

		data.set(pos_arr + 1, x + value);
	}
}

big_integer::big_integer() {
	data.push_back(0);
	sign = 0;
}

big_integer::big_integer(big_integer const& other) : data(other.data), sign(other.sign) {}

big_integer::big_integer(int value) {
	long long long_value = value;
	sign = 0;
	if (long_value < 0) {
		long_value = -long_value;
		sign = ~sign;
	}
	data.push_back((unsigned)long_value);
	change();
}

big_integer::big_integer(string const& str) {
	big_integer(); // инициализируем нулем
	if (!str.empty()) {
		size_t pos = 0;
		unsigned sign_rhs = 0;
		if (str[pos] == '-') {
			++pos;
			sign_rhs = ~sign_rhs;
		}
		if (pos != str.length()) {
			for (; pos < str.length(); ++pos) {
				*this = (*this * 10) + (str[pos] - '0');
			}
			if ((sign_rhs) && (*this != 0)) {
				sign = sign_rhs;
				change();
			}
		}
	}
}

big_integer& big_integer::operator+=(big_integer const& rhs) {
	*this = *this + rhs;
	return *this;
}

big_integer& big_integer::operator-=(big_integer const& rhs) {
	*this = *this - rhs;
	return *this;
}

big_integer& big_integer::operator*=(big_integer const& rhs) {
	*this = *this * rhs;
	return *this;
}

big_integer& big_integer::operator/=(big_integer const& rhs) {
	*this = *this / rhs;
	return *this;
}

big_integer& big_integer::operator%=(big_integer const& rhs) {
	*this = *this % rhs;
	return *this;
}

big_integer& big_integer::operator&=(big_integer const& rhs) {
	*this = (*this) & rhs;
	return *this;
}

big_integer& big_integer::operator|=(big_integer const& rhs) {
	*this = (*this) | rhs;
	return *this;
}

big_integer& big_integer::operator^=(big_integer const& rhs) {
	*this = (*this) ^ rhs;
	return *this;
}

big_integer& big_integer::operator<<=(int rhs) {
	*this = ((*this) << rhs);
	return *this;
}

big_integer& big_integer::operator>>=(int rhs) {
	*this = ((*this) >> rhs);
	return *this;
}

big_integer& big_integer::operator=(big_integer rhs) {
	swap(rhs, *this);
	return *this;
}

big_integer big_integer::operator+() const {
	return *this;
}

big_integer big_integer::operator-() const {
	big_integer temp = *this;
	if (temp == 0) return temp;
	temp.data.push_back(sign);
	temp.change();
	temp.sign = ~temp.sign;
	temp.change();
	return temp.normalize();
}

big_integer big_integer::operator~() const {
	big_integer temp = *this;
	temp.sign = ~temp.sign;
	for (size_t i = 0; i < temp.data.size(); ++i) {
		temp.data.set(i, ~temp.data.get(i));
	}
	return temp.normalize();
}

// not in class

void swap(big_integer &a, big_integer &b) {
	swap(a.data, b.data);
	swap(a.sign, b.sign);
}

big_integer operator+(big_integer const& a, big_integer const& b) {
	big_integer temp;
	temp.data.clear();
	size_t max_len = max(a.data.size(), b.data.size());
	unsigned long long carry = 0, c1, c2;
	
	for (size_t i = 0; i < max_len + 2; ++i) {
		c1 = (i < a.data.size() ? a.data.get(i) : a.sign);
		c2 = (i < b.data.size() ? b.data.get(i) : b.sign);
		carry += c1 + c2;
		temp.data.push_back((unsigned)carry);
		carry >>= sz;
	}
	carry += a.sign + b.sign;
	temp.sign = (unsigned)(carry);
	return temp.normalize();
}

big_integer operator-(big_integer const& a, big_integer const& b) {
	return a + (-b);
}

big_integer operator*(big_integer lhs, unsigned const& b) {
	unsigned sign1 = lhs.sign;
	lhs.change();
	lhs.sign = 0;

	unsigned sign2 = 0;
	long long rhs = b;
	if (rhs < 0) {
		rhs = -rhs;
		sign2 = ~sign2;
	}

	big_integer temp;
	temp.data.clear();
	size_t len = lhs.data.size();
	unsigned long long carry = 0, c1, c2 = rhs;

	for (size_t i = 0; i < len + 3; ++i) {
		c1 = (i < lhs.data.size() ? lhs.data.get(i) : 0);
		carry += c1 * c2;
		temp.data.push_back((unsigned)carry);
		carry >>= sz;
	}

	if ((sign1 ^ sign2) && (temp != 0)) {
		temp.sign = sign1 ^ sign2;
		temp.change();
	}
	return temp.normalize();
}

big_integer operator*(big_integer a, big_integer b) {
	unsigned sign1 = a.sign;
	a.change();
	a.sign = 0;

	unsigned sign2 = b.sign;
	b.change();
	b.sign = 0;

	big_integer temp, t;

	for (size_t i = 0; i < b.data.size(); ++i) { // O(nm) !
		t = a * b.data.get(i);
		for (size_t j = 0; j < i; ++j) {
			t.data.push_back(0);
		}
		for (size_t j = t.data.size() - 1; j >= 0; --j) {
			t.data.set(j, (j >= i ? t.data.get(j - i) : 0));
			if (j == 0) break;
		}
		temp += t;
	}

	if ((sign1 ^ sign2) && (temp != 0)) {
		temp.sign = sign1 ^ sign2;
		temp.change();
	}
	return temp.normalize();
}

big_integer operator/(big_integer a, big_integer b) {
	unsigned sign1 = a.sign;
	a.change();
	a.sign = 0;

	unsigned sign2 = b.sign;
	b.change();
	b.sign = 0;
	
	if (a < b) return 0;

	a.data.push_back(0);
	a.data.reverse();
	b.data.reverse();

	int len = (a.data.size() - b.data.size());

	big_integer temp;
	for (size_t i = 0; i <= a.data.size(); ++i) {
		temp.data.push_back(0);
	}

	bool gr;
	unsigned c1, c2;

	len = len * sz;
	for (int i = 0; i <= len; ++i) {
		gr = true;
		for (int j = -1; j < (int)b.data.size(); ++j) {
			c1 = (i + j * int(sz) >= 0 ? a.get_block(i + j * sz) : 0);
			c2 = (j >= 0 ? b.data.get(j) : 0);
			if (c1 > c2) break;
			if (c1 < c2) {
				gr = false;
				break;
			}
		}
		if (!gr) {
			temp.set_bit((len - i), 0);
			continue;
		}
		// будем отнимать!
		temp.set_bit(len - i, 1);

		long long carry = 0, cur, base;
		base = 1; base <<= sz;
		for (int j = b.data.size() - 1; j >= -1; --j) {
			if (i + j * int(sz) < 0) break;
			c1 =  a.get_block(i + j * sz);
			c2 = (j >= 0 ? b.data.get(j) : 0);
			cur = c1;
			cur = cur - c2 - carry;
			if (cur < 0) {
				cur += base;
				carry = 1;
			} else
			{
				carry = 0;
			}
			a.set_block(i + j * sz, (unsigned)cur);
		}
	}

	if ((sign1 ^ sign2) && (temp != 0)) {
		temp.sign = sign1 ^ sign2;
		temp.change();
	}
	return temp.normalize();
}

big_integer operator%(big_integer a, big_integer b) {
	unsigned sign1 = a.sign;
	a.change();
	a.sign = 0;

	b.change();
	b.sign = 0;

	big_integer temp = a - (a / b) * b;

	if ((sign1) && (temp != 0)) {
		temp.sign = sign1;
		temp.change();
	}
	return temp.normalize();
}

big_integer operator&(big_integer const& a, big_integer const& b) {
	big_integer temp;
	temp.sign = a.sign & b.sign;
	size_t max_len = max(a.data.size(), b.data.size());
	unsigned c1, c2;
	for (size_t i = 0; i < max_len; ++i) {
		c1 = (i < a.data.size() ? a.data.get(i) : a.sign);
		c2 = (i < b.data.size() ? b.data.get(i) : b.sign);
		temp.data.set(i, c1 & c2);
	}
	return temp.normalize();
}

big_integer operator|(big_integer const& a, big_integer const& b) {
	big_integer temp;
	temp.sign = a.sign | b.sign;

	size_t max_len = max(a.data.size(), b.data.size());
	unsigned c1, c2;
	for (size_t i = 0; i < max_len; ++i) {
		c1 = (i < a.data.size() ? a.data.get(i) : a.sign);
		c2 = (i < b.data.size() ? b.data.get(i) : b.sign);
		temp.data.set(i, c1 | c2);
	}
	return temp.normalize();
}

big_integer operator^(big_integer const& a, big_integer const& b) {
	big_integer temp;
	temp.sign = a.sign ^ b.sign;

	size_t max_len = max(a.data.size(), b.data.size());
	unsigned c1, c2;
	for (size_t i = 0; i < max_len; ++i) {
		c1 = (i < a.data.size() ? a.data.get(i) : a.sign);
		c2 = (i < b.data.size() ? b.data.get(i) : b.sign);
		temp.data.set(i, c1 ^ c2);
	}
	return temp.normalize();
}

big_integer operator<<(big_integer const& a, int b) {
	big_integer temp = a;

	temp.data.push_back(temp.sign);
	unsigned len = sz * temp.data.size(), bit;
	for (int i = len - 1; i >= 0; --i) {
		if (i - b >= 0) {
			bit = temp.get_bit(i - b);
			temp.set_bit(i, bit);
		} else
		{
			temp.set_bit(i, 0);
		}
	}
	temp.sign = temp.data.back();
	temp.data.pop_back();
	return temp.normalize();
}

big_integer operator>>(big_integer const& a, int b) {
	big_integer temp = a;

	temp.data.push_back(temp.sign);
	unsigned len = sz * temp.data.size(), bit;
	for (size_t i = 0; i < len; ++i) {
		if (i + b < len) {
			bit = temp.get_bit(i + b);
			temp.set_bit(i, bit);
		} else
		{
			temp.set_bit(i, temp.sign ? 1 : 0);
		}
	}
	temp.sign = temp.data.back();
	temp.data.pop_back();
	return temp.normalize();
}

bool operator==(big_integer const& a, big_integer const& b) {
	return compare(a, b) == 0;
}

bool operator!=(big_integer const& a, big_integer const& b) {
	return compare(a, b) != 0;
}

bool operator<(big_integer const& a, big_integer const& b) {
	return compare(a, b) < 0;
}

bool operator>(big_integer const& a, big_integer const& b) {
	return compare(a, b) > 0;
}

bool operator<=(big_integer const& a, big_integer const& b) {
	return compare(a, b) <= 0;
}

bool operator>=(big_integer const& a, big_integer const& b) {
	return compare(a, b) >= 0;
}

string to_string(big_integer a) {
	string res;
	unsigned sign = a.sign;
	big_integer c;
	if (a < 0) a = -a;
	if (a == 0) return "0";
	while (a > 0) {
		c = a % 10;
		a = a / 10;
		res = (char)(c.data.front() + '0') + res;
	}
	if (sign) res = '-' + res;
	return res;
}
