#pragma once

#include <memory>
#include <ostream>
#include <stdexcept>

template <typename T>
class Vector {
public:
	Vector() : _size(0), _capacity(0) {}

	/**
	 * Creates a vector of size n with values default_val.
	 */
	Vector(size_t n, const T& default_val) : _size(n), _capacity(n)
	{

		_data = std::make_unique<T[]>(n);
		for (size_t i = 0; i < n; ++i) {
			_data[i] = default_val;
		}
	}

	/**
	 * Creates a vector containing the elements in l.
	 */
	Vector(std::initializer_list<T> l) : _size(l.size()), _capacity(l.size()) {
		_data = std::make_unique<T[]>(l.size());
		size_t i = 0;
		for (const auto& val : l) {
			_data[i++] = val;
		}
	}

	Vector(const Vector& copy) : _size(copy._size), _capacity(copy._capacity) {
		_data = std::make_unique<T[]>(_capacity);
		std::copy(copy._data.get(), copy._data.get() + _size, _data.get());
	}

	Vector(Vector&& move) : _size(move._size), _capacity(move._capacity), _data(std::move(move._data)) {
	}

	/**
	 * Replaces the contents of the vector.
	 */
	Vector& operator=(const Vector& copy) {
		_size = copy._size;
		_capacity = copy._capacity;
		_data = std::make_unique<T[]>(_capacity);
		std::copy(copy._data.get(), copy._data.get() + _size, _data.get());
		return *this;
	}


	/**
	 * Replaces the contents of the vector.
	 */
	Vector& operator=(Vector&& move) noexcept {
		_size = move._size;
		_capacity = move._capacity;
		_data = std::move(move._data);
		return *this;
	}

	size_t size() const noexcept { return _size; }

	size_t capacity() const noexcept { return _capacity; }

	/**
	 * Appends the given element value to the end of the vector.
	 */
	void push_back(const T& value) {
		if (_size == _capacity) {
			resize(_capacity * growth_factor);
		}
		_data[_size++] = value;
	}

	/**
	 * Appends the given element value to the end of the vector.
	 */
	void push_back(T&& value) {
		if (_size == _capacity) {
			resize(_capacity * growth_factor);
		}
		_data[_size++] = std::move(value);
	}

	/**
	 * Removes the last element of the vector.
	 */
	void pop_back() {
		if (_size > 0) {
			--_size;
		}
	}

	/**
	 * Returns a reference to the element at specified location pos, with bounds checking.
	 * If pos is not within the range of the vector, an exception of type std::out_of_range is thrown.
	 */
	T& at(const size_t pos) const {
		if (pos >= _size) {
			throw std::out_of_range("Index out of range");
		}
		return _data[pos];
	}

	/**
	 * Returns a reference to the element at specified location pos, with bounds checking.
	 * If pos is not within the range of the vector, an exception of type std::out_of_range is thrown.
	 */
	T& at(const size_t pos) {
		if (pos >= _size) {
			throw std::out_of_range("Index out of range");
		}
		return _data[pos];
	}

	/**
	 * Returns a reference to the element at specified location pos.
	 * No bounds checking is performed.
	 */
	T& operator[](const size_t index) const {
		return _data[index];
	}

	/**
	 * Returns a reference to the element at specified location pos.
	 * No bounds checking is performed.
	 */
	T& operator[](const size_t index) {
		return _data[index];
	}

	friend std::ostream& operator<<(std::ostream& o, Vector<T> v) {
		o << "Size: " << v._size << ", Capacity: " << v._capacity << std::endl;
		for (size_t i = 0; i < v._size; ++i) {
			if (i > 0)
				o << ", ";
			o << v._data[i];
		}
		o << std::endl;
		return o;
	}

	~Vector() = default;

private:
	// Defines how the `_capacity` is increased.
	size_t growth_factor = 2;
	size_t _size;
	size_t _capacity;

	// Holds vector's data.
	std::unique_ptr<T[]> _data;

	/**
	 * Calculates the necessary capacity for new_size.
	 * If necessary, double `_capacity` using `growth_factor`.
	 */
	size_t calculate_capacity(size_t new_size) {
		size_t new_capacity = _capacity;
		while (new_size > new_capacity) {
			new_capacity *= growth_factor;
		}
		return new_capacity;
	}

	/**
	* Resizes the vector to new_capacity.
	* If the current capacity is less than new_capacity
	* the vector moves all elements to a new array.
	*/
	void resize(size_t new_capacity) {
		auto new_data = std::make_unique<T[]>(new_capacity);
		std::copy(_data.get(), _data.get() + _size, new_data.get());
		_data = std::move(new_data);
		_capacity = new_capacity;
	}
};
