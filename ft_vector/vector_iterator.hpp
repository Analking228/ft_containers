#pragma once

#include <iterator>
#include "../utils.hpp"

namespace ft
{
	template <class T, class Pointer = T*, class Reference = T&, class Category = std::random_access_iterator_tag, class allocator_type = std::allocator<T> >
	class vector_iterator{
	public:
		typedef typename ft::iterator_traits<T>::value_type			value_type;
		typedef typename ft::iterator_traits<T>::reference			reference;
		typedef typename ft::iterator_traits<T>::const_reference	const_reference;
		typedef typename ft::iterator_traits<T>::pointer			pointer;
		typedef typename ft::iterator_traits<T>::const_pointer		const_pointer;
		typedef typename ft::iterator_traits<T>::size_type			size_type;
    	typedef typename ft::iterator_traits<T>::difference_type	difference_type;
		typedef Category											iterator_category;

	private:
		pointer _Ptr;

	public:
		vector_iterator (pointer _Ptr = 0): _Ptr(_Ptr) {};
		
		vector_iterator (const vector_iterator & other): _Ptr(other._Ptr) {}
		vector_iterator operator=(const vector_iterator & other) {
			_Ptr = other._Ptr;
			return *this;
		}
		bool operator==(const vector_iterator & it) const {
			return (_Ptr == it._Ptr);
		}
		bool operator!=(const vector_iterator & it) const {
			return (_Ptr != it._Ptr);
		}
		bool operator>=(const vector_iterator & it) const {
			return (_Ptr >= it._Ptr);
		}
		bool operator<=(const vector_iterator & it) const {
			return (_Ptr <= it._Ptr);
		}
		bool operator>(const vector_iterator & it) const {
			return (_Ptr > it._Ptr);
		}
		bool operator<(const vector_iterator & it) const {
			return (_Ptr < it._Ptr);
		}
		reference operator*() {
			return(*_Ptr);
		}
		const_reference operator*() const {
			return(*_Ptr);
		}
		pointer operator->() {
			return (_Ptr);
		}
		const_pointer operator->() const {
			return (_Ptr);
		}
		vector_iterator & operator++() {
			_Ptr++;
			return (*this);
		}
		pointer base() {
			return _Ptr;
		}
		const_pointer base() const {
			return _Ptr;
		}
		vector_iterator operator++(int) {
			vector_iterator result = *this;
			++(*this);
			return (result);
		}
		vector_iterator & operator--() {
			_Ptr--;
			return (*this);
		}
		vector_iterator operator--(int) {
			vector_iterator result = *this;
			--(*this);
			return (result);
		}
		vector_iterator & operator+=(difference_type n) {
			_Ptr += n;
			return (*this);
		}
		vector_iterator & operator-=(difference_type n) {
			_Ptr -= n;
			return (*this);
		}
		vector_iterator operator+(difference_type n) const {
			return (_Ptr + n);
		}
		vector_iterator operator-(difference_type n) const {
			return (_Ptr - n);
		}
		difference_type operator-(vector_iterator it) const {
			return (_Ptr - it._Ptr);
		}
		reference operator[](difference_type i) const {
			return (*(_Ptr + i));
		}
		operator vector_iterator<const T> () const {
			return (vector_iterator<const T>(_Ptr));
		}
	};
	
	template <typename T>
	bool operator==(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right) {
		return (left.base() == right.base());
	}
	
	template <typename T>
	bool operator!=(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right) {
		return (left.base() != right.base());
	}
	
	template <typename T>
	bool operator<(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right) {
		return (left.base() < right.base());
	}
	
	template <typename T>
	bool operator>(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right) {
		return (left.base() > right.base());
	}
	
	template <typename T>
	bool operator<=(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right) {
		return (left.base() <= right.base());
	}
	
	template <typename T>
	bool operator>=(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right) {
		return (left.base() >= right.base());
	}

	template <typename T>
	typename ft::vector_iterator<T>::difference_type operator-(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right) {
		return (left.base() - right.base());
	}

	template<typename T>
	ft::vector_iterator<T> operator+(typename ft::vector_iterator<T>::difference_type n, typename ft::vector_iterator<T>& rai) {
			return (&(*rai) + n);
	}

	template<typename T_L, typename T_R>
	bool operator==(const ft::vector_iterator<T_L> left, const ft::vector_iterator<T_R> right) {
		return (left.base() == right.base());
	}
	
	template<typename T_L, typename T_R>
	bool operator!=(const ft::vector_iterator<T_L> left, const ft::vector_iterator<T_R> right) {
		return (left.base() != right.base());
	}
	
	template<typename T_L, typename T_R>
	bool operator<(const ft::vector_iterator<T_L> left, const ft::vector_iterator<T_R> right) {
		return (left.base() < right.base());
	}
	
	template<typename T_L, typename T_R>
	bool operator>(const ft::vector_iterator<T_L> left, const ft::vector_iterator<T_R> right) {
		return (left.base() > right.base());
	}

	template<typename T_L, typename T_R>
	bool operator<=(const ft::vector_iterator<T_L> left, const ft::vector_iterator<T_R> right) {
		return (left.base() <= right.base());
	}

	template<typename T_L, typename T_R>
	bool operator>=(const ft::vector_iterator<T_L> left, const ft::vector_iterator<T_R> right) {
		return (left.base() >= right.base());
	}

	template<typename T_L, typename T_R>
	typename ft::vector_iterator<T_L>::difference_type operator-(const ft::vector_iterator<T_L> left, const ft::vector_iterator<T_R> right) {
		return (left.base() - right.base());
	}
}