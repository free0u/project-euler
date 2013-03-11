#include "Vector.h"
#include <cassert>
#include <algorithm>
#include <memory.h>

void Vector::erase_data() {
	if (data_size > 0) {
		delete[] data;
		data_size = 0;
	}
}

void Vector::ensure_capacity_data(size_t cap) {
	if (cap > data_size) {
		size_t new_data_size = 1;
		while (new_data_size < cap) {
			new_data_size <<= 1;
		}
		unsigned* temp = new unsigned[new_data_size];
		memcpy(temp, data, cnt_elem * sizeof(unsigned));
		erase_data();
		data_size = new_data_size;
		data = temp;
	}
}

void Vector::copy_on_write() {
	if ((*cnt_reference) > 1) { // не можем менять данные, надо скопировать
		if (cnt_elem > inplace_cnt) {
			unsigned* temp = new unsigned[data_size];
			memcpy(temp, data, data_size * sizeof(unsigned));
			data = temp;
		}
		cnt_reference = new unsigned(1);
	}
}

Vector::Vector() {
	cnt_reference = new unsigned(1);

	cnt_elem = 0;
	data_size = 0;
}

Vector::Vector(Vector const& other) {
	if (other.cnt_elem <= other.inplace_cnt) {
		memcpy(inplace_data, other.inplace_data, other.cnt_elem * sizeof(unsigned));
	} else
	{
		data = other.data;
	}
	cnt_elem = other.cnt_elem;
	data_size = other.data_size;
	cnt_reference = other.cnt_reference;

	++(*cnt_reference);
}

Vector::~Vector() {
	if ((*cnt_reference) == 1) {
		clear();
		delete cnt_reference;
	} else 
	{
		--(*cnt_reference);
	}
}

void Vector::push_back(unsigned value) {
	copy_on_write();

	if (cnt_elem < inplace_cnt) {
		inplace_data[cnt_elem] = value;
		++cnt_elem;
	} else
	{
		if (cnt_elem == inplace_cnt) { // надо перенести данные из inplace в data и добавить новый
			unsigned* temp = new unsigned[inplace_cnt];
			memcpy(temp, inplace_data, inplace_cnt * sizeof(unsigned));
			
			erase_data();
			data_size = inplace_cnt;
			data = temp;

			ensure_capacity_data(inplace_cnt + 1);
			data[cnt_elem] = value;
			cnt_elem++;
		} else { // просто добавить элемент в data
			ensure_capacity_data(cnt_elem + 1);
			data[cnt_elem] = value;
			++cnt_elem;
		}
	}
}

unsigned Vector::back() {
	assert(cnt_elem > 0);
	return get(cnt_elem - 1);
}

unsigned Vector::front() {
	assert(cnt_elem > 0);
	return get(0);
}

void Vector::pop_back() {
	assert(cnt_elem > 0);
	
	copy_on_write();

	if (cnt_elem <= inplace_cnt) {
		--cnt_elem;
	} else
	{
		--cnt_elem;

		// переносим данные в inplace если нужно
		if (cnt_elem <= inplace_cnt) {
			unsigned* temp = data;
			memcpy(inplace_data, temp, cnt_elem * sizeof(unsigned));
			delete[] temp;
			data_size = 0;
		} else // уменьшить data если надо
		{
			if (cnt_elem < data_size / 4) {
				size_t new_data_size = data_size / 2;
				unsigned* temp = new unsigned[new_data_size];
				memcpy(temp, data, cnt_elem * sizeof(unsigned));

				erase_data();
				data_size = new_data_size;
				data = temp;
			}
		}
	}
}

size_t Vector::size() const {
	return cnt_elem;
}

void Vector::set(size_t ind, unsigned value) {
	assert(ind >= 0 && ind < cnt_elem);

	copy_on_write();

	if (cnt_elem <= inplace_cnt) {
		inplace_data[ind] = value;
	} else 
	{
		assert(ind < data_size);
		data[ind] = value;
	}
}

unsigned Vector::get(size_t ind) const {
	assert(ind >= 0 && ind < cnt_elem);
	if (cnt_elem <= inplace_cnt) {
		return inplace_data[ind];
	} else
	{
		assert(ind < data_size);
		return data[ind];
	}
}

void Vector::clear() {
	copy_on_write();

	cnt_elem = 0;
	erase_data();
}

void Vector::assign(size_t count, unsigned value) {
	copy_on_write();

	clear();
	for (size_t i = 0; i < count; ++i) {
		push_back(value);
	}
}

void Vector::resize(size_t count) {
	copy_on_write();

	clear();
	for (size_t i = 0; i < count; ++i) {
		push_back(0);
	}
}

void Vector::reverse() {
	copy_on_write();

	if (cnt_elem <= inplace_cnt) {
		std::reverse(inplace_data, inplace_data + cnt_elem);
	} else
	{
		std::reverse(data, data + cnt_elem);
	}
}

Vector& Vector::operator=(Vector rhs) {
	copy_on_write();

	swap(*this, rhs);
	return *this;
}

void swap(Vector& a, Vector& b) {
	a.copy_on_write();
	b.copy_on_write();

	std::swap(a.cnt_elem, b.cnt_elem);
	std::swap(a.data_size, b.data_size);
	std::swap(a.inplace_data, b.inplace_data);
	std::swap(*a.cnt_reference, *b.cnt_reference);
}