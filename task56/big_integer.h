#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include "Vector.h"
#include <vector>
#include <string>
#include <algorithm>

//typedef std::vector<unsigned> Vector;

class big_integer {
public:
	Vector data;
	unsigned sign;

	unsigned get_block(int i);
	void set_block(int i, unsigned value);
	void change();
	big_integer& normalize();
	unsigned get_bit(unsigned);
	void set_bit(unsigned, unsigned);
public:
	big_integer();
	big_integer(big_integer const& other);
	big_integer(int);
	explicit big_integer(std::string const& str);

	big_integer& operator+=(big_integer const& rhs);
	big_integer& operator-=(big_integer const& rhs);
	big_integer& operator*=(big_integer const& rhs);
	big_integer& operator/=(big_integer const& rhs);
	big_integer& operator%=(big_integer const& rhs);

	big_integer& operator&=(big_integer const& rhs);
	big_integer& operator|=(big_integer const& rhs);
	big_integer& operator^=(big_integer const& rhs);

	big_integer& operator<<=(int rhs);
	big_integer& operator>>=(int rhs);

	big_integer& operator=(big_integer rhs);

	big_integer operator+() const;
	big_integer operator-() const;
	big_integer operator~() const;

	friend int compare(big_integer const& a, big_integer const& b);
	friend void swap(big_integer& a, big_integer& b);

	friend big_integer operator+(big_integer const& a, big_integer const& b);
	friend big_integer operator-(big_integer const& a, big_integer const& b);
	friend big_integer operator*(big_integer lhs, unsigned const& b);
	friend big_integer operator*(big_integer a, big_integer b);
	friend big_integer operator/(big_integer a, big_integer b);
	friend big_integer operator%(big_integer a, big_integer b);

	friend big_integer operator&(big_integer const& a, big_integer const& b);
	friend big_integer operator|(big_integer const& a, big_integer const& b);
	friend big_integer operator^(big_integer const& a, big_integer const& b);

	friend big_integer operator<<(big_integer const& a, int b);
	friend big_integer operator>>(big_integer const& a, int b);

	friend std::string to_string(big_integer a);

};

int compare(big_integer const& a, big_integer const& b);
void swap(big_integer& a, big_integer& b);

big_integer operator+(big_integer const& a, big_integer const& b);
big_integer operator-(big_integer const& a, big_integer const& b);
big_integer operator*(big_integer lhs, unsigned const& b);
big_integer operator*(big_integer a, big_integer b);
big_integer operator/(big_integer a, big_integer b);
big_integer operator%(big_integer a, big_integer b);

big_integer operator&(big_integer const& a, big_integer const& b);
big_integer operator|(big_integer const& a, big_integer const& b);
big_integer operator^(big_integer const& a, big_integer const& b);

big_integer operator<<(big_integer const& a, int b);
big_integer operator>>(big_integer const& a, int b);

bool operator==(big_integer const& a, big_integer const& b);
bool operator!=(big_integer const& a, big_integer const& b);
bool operator<(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);

std::string to_string(big_integer a);

#endif // BIG_INTEGER_H
