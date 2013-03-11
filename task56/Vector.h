#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <iostream>

class Vector {
	static const size_t inplace_cnt = 8;
	size_t cnt_elem, data_size;

	unsigned* cnt_reference;

	union {
		unsigned* data;
		unsigned inplace_data[inplace_cnt];
	};
	
	void erase_data();
	void ensure_capacity_data(size_t cap);
	void copy_on_write();
public:
	Vector();
	Vector(Vector const& other);
	~Vector();
	void push_back(unsigned value);
	unsigned front();
	unsigned back();
	void pop_back();
	size_t size() const;
	void set(size_t ind, unsigned value);
	unsigned get(size_t ind) const;
	void clear();
	void assign(size_t count, unsigned value);
	void resize(size_t count);
	void reverse();
	Vector& operator=(Vector rhs);

	friend void swap(Vector& a, Vector& b);
};


void swap(Vector& a, Vector& b);


#endif // MY_VECTOR_H


