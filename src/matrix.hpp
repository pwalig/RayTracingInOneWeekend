#pragma once

#include <vector>
#include <cassert>
#include <type_traits>

template <typename T>
class matrix {
private:

	// proxy object representing one row of the matrix
	template <typename U>
    class row_view {
	public:
		using size_type = typename std::vector<T>::size_type;

    private:
        row_view(U* data_, size_type size_) : data(data_), size(size_) { }
        U* const data;
        const size_type size;

    public:
		// iterator

		template <typename V>
		class iter {
		public:
			using iterator_category = std::random_access_iterator_tag;
			using difference_type   = std::ptrdiff_t;
			using value_type        = V;
			using pointer           = value_type*;
			using reference         = value_type&;
		private:
			pointer ptr;

		public:
			inline iter(pointer ptr) : ptr(ptr) {}

			inline reference operator*() const { return *ptr; }
			inline pointer operator->() { return ptr; } 

			inline iter& operator++() { ++ptr; return *this; }  
			inline iter operator++(int) { iter tmp = *this; ++(*this); return tmp; }
			inline iter& operator--() { --ptr; return *this; }
			inline iter operator--(int) { iter tmp = *this; --(*this); return tmp; }
            inline iter& operator+=(difference_type n) { ptr += n; return *this; }
			inline iter& operator-=(difference_type n) { ptr -= n; return *this; }

            friend inline bool operator== (const iter& a, const iter& b) { return a.ptr == b.ptr; }
            friend inline bool operator!= (const iter& a, const iter& b) { return !(a == b); }
			friend inline bool operator<(const iter& lhs, const iter& rhs) { return lhs.ptr < rhs.ptr; }
			friend inline bool operator>(const iter& lhs, const iter& rhs) { return rhs < lhs; }
			friend inline bool operator<=(const iter& lhs, const iter& rhs) { return !(rhs < lhs); }
			friend inline bool operator>=(const iter& lhs, const iter& rhs) { return !(lhs < rhs); }

			friend inline iter operator+(const iter& it, difference_type n) {
				iter temp = it;
				temp += n;
				return temp;
			}
			friend inline iter operator+(difference_type n, const iter& it) { return it + n; }
			friend inline iter operator-(const iter& it, difference_type n) {
				iter temp = it;
				temp -= n;
				return temp;
			}
			friend inline difference_type operator-(const iter& lhs, const iter& rhs) { return lhs.ptr - rhs.ptr; }
		};

		// types

		using value_type = U;
		using reference = U&;
		using pointer = U*;
		using iterator = iter<typename std::remove_const<U>::type>;
		using const_iterator = iter<typename std::add_const<U>::type>;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		U& operator[](size_type ind) const { return data[ind]; }

        friend class matrix<T>;

		const_iterator begin() const { return const_iterator(data); }
		const_iterator end() const { return const_iterator(data + size); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(data); }
		const_reverse_iterator rend() const { return const_reverse_iterator(data + size); }
    };
    
public:
	// iterator
	template <typename U>
	class iter {
	public:
		using iterator_category = std::random_access_iterator_tag;
		using difference_type   = std::ptrdiff_t;
		using value_type        = row_view<U>;
		using pointer           = U*;
		//using reference         = value_type&;
	private:
		pointer ptr;
		const size_t len;

	public:
		inline iter(pointer ptr, size_t rowLength) : ptr(ptr), len(rowLength) {}

		//reference operator*() const { return *m_ptr; }
		//pointer operator->() { return m_ptr; } 
		inline value_type operator*() { return value_type(ptr, len); }

		inline iter& operator++() { ptr += len; return *this; }  
		inline iter operator++(int) { iter tmp = *this; ++(*this); return tmp; }
		inline iter& operator--() { ptr -= len; return *this; }
		inline iter operator--(int) { iter tmp = *this; --(*this); return tmp; }
		inline iter& operator+=(difference_type n) { ptr += n * len; return *this; }
		inline iter& operator-=(difference_type n) { ptr -= n * len; return *this; }

		friend inline bool operator== (const iter& a, const iter& b) { return a.ptr == b.ptr; }
		friend inline bool operator!= (const iter& a, const iter& b) { return !(a == b); }
		friend inline bool operator<(const iter& lhs, const iter& rhs) { return lhs.ptr < rhs.ptr; }
		friend inline bool operator>(const iter& lhs, const iter& rhs) { return rhs < lhs; }
		friend inline bool operator<=(const iter& lhs, const iter& rhs) { return !(rhs < lhs); }
		friend inline bool operator>=(const iter& lhs, const iter& rhs) { return !(lhs < rhs); }

		friend inline iter operator+(const iter& it, difference_type n) {
			iter temp = it;
			temp += n;
			return temp;
		}
		friend inline iter operator+(difference_type n, const iter& it) { return it + n; }
		friend inline iter operator-(const iter& it, difference_type n) {
			iter temp = it;
			temp -= n;
			return temp;
		}
		friend inline difference_type operator-(const iter& lhs, const iter& rhs) {
			assert(lhs.len == rhs.len);
			return (lhs.ptr - rhs.ptr) / lhs.len;
		}
	};

	// types

	using value_type = T;
	using size_type = typename std::vector<T>::size_type;
	using reference = value_type&;
	using pointer = value_type*;
	using iterator = iter<T>;
	using const_iterator = iter<const T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
	// private members

    std::vector<T> _data;
    size_type _x;
    size_type _y;

public:

	// constructors destructors operators

    matrix(size_type x, size_t y) : _data(x * y), _x(x), _y(y) {}
    matrix(size_type x, size_t y, const T& elem) : _data(x * y, elem), _x(x), _y(y) {}
	matrix(const matrix& other) : _data(other._data), _x(other._x), _y(other._y) {}
	matrix(matrix&& other) : _data(other._data), _x(other._x), _y(other._y) {}

	matrix& operator=(const matrix& other) {
		if (this != &other) {
			_data = other._data;
			_x = other._y;
			_y = other._y;
		}
	}
	matrix& operator=(matrix&& other) {
		if (this != &other) {
			_data = other._data;
			_x = other._y;
			_y = other._y;
		}
	}

	inline friend bool operator== (const matrix& a, const matrix& b)
	{ return a._x == b._x && a._y == b._y && a._data == b._data; }
	inline friend bool operator!= (const matrix& a, const matrix& b) { return !(a == b); }

    row_view<T> operator[](size_type ind) { return row_view<T>(&_data[ind * _y], _y); }
    const row_view<const T> operator[](size_type ind) const { return row_view<const T>(&_data[ind * _y], _y); }

	// methods

	T* data() { return _data.data(); }
	const T* data() const { return _data.data(); }
	size_type size() const { return _data.size(); }
	// implementation of resize is currently suboptimal
	void resize(size_type x, size_t y) {
		matrix<T> temp = *this;
		_data.resize(x * y);
		_x = x;
		_y = y;
		for (size_type i = 0; i < std::min(temp.x(), _x); ++i) {
			for (size_type j = 0; j < std::min(temp.y(), _y); ++j) {
				(*this)[i][j] = temp[i][j];
			}
		}
	}
	size_type capacity() const { return _data.capacity(); }
	void reserve(size_type new_capacity) { _data.reserve(new_capacity); }
	void shrink_to_fit() { _data.shrink_to_fit(); }
	void clear() { _data.clear(); _x = 0; _y = 0; }
	size_type x() const { return _x; }
	size_type y() const { return _y; }


	iterator begin() { return iterator(_data.data(), _y); }
	iterator end() { return iterator(_data.data() + _data.size(), _y); }

	const_iterator begin() const { return const_iterator(_data.data(), _y); }
	const_iterator end() const { return const_iterator(_data.data() + _data.size(), _y); }

	const_iterator cbegin() const { return const_iterator(_data.data(), _y); }
	const_iterator cend() const { return const_iterator(_data.data() + _data.size(), _y); }

};
