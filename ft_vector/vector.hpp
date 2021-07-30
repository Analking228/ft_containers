#pragma once

#include <algorithm>
#include <cstdlib>

#include "vector_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../utils.hpp"

namespace ft{
	
	// class?
	template < class T, class Allocator = std::allocator<T> >

	// class MyVector {
	class vector {
	public:
		/*DEFENITIONS*/
		typedef T											value_type;
		typedef typename Allocator::reference				reference;
		typedef typename Allocator::const_reference			const_reference;
		typedef typename Allocator::const_pointer			const_pointer;
		typedef typename Allocator::difference_type			difference_type;
		typedef typename Allocator::pointer					pointer;
		typedef typename Allocator::size_type				size_type;
		typedef ft::vector_iterator<T>						iterator;
		typedef ft::vector_iterator<const T>				const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		pointer												_Ptr;
		Allocator	 										_Alloc;
		size_type											_Size;
		size_type											_Capacity;
	
	public:
		/*MEM-FUNCS*/
		explicit vector(Allocator const & _Alloc = Allocator()):  _Ptr(0),_Alloc(_Alloc), _Size(0), _Capacity(0){}
		vector(size_type n, value_type const & val = value_type(), Allocator const & alloc = Allocator()):_Alloc(alloc),_Size(n),_Capacity(n) {
			_Ptr = _Alloc.allocate(n);	
			
			for (size_type i = 0; i < n; i++)
				_Alloc.construct(_Ptr + i, val);
		}
         template <class InputIt> vector (InputIt first, InputIt last, Allocator const & alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0): _Alloc(alloc) {
			_Size = 0;
			
			for (InputIt i = first; i != last; i++)
				_Size++;
			for (_Capacity = 1; _Capacity < _Size;)
				_Capacity *= 2;
			_Ptr = _Alloc.allocate(_Capacity);
			for (size_type i = 0; i < _Size; i++, first++)
				_Alloc.construct(_Ptr + i, *first);
		}
		vector(const vector & other):_Ptr(other._Ptr),_Alloc(other._Alloc),_Size(other._Size),_Capacity(other._Capacity) {
			_Ptr = _Alloc.allocate(_Capacity);
			
			pointer first = (pointer)other.begin().operator->();
			for (size_type i = 0; i < _Size; i++, first++)
				_Alloc.construct(_Ptr + i, *first);
		}
		~vector() {
			for (size_type i = 0; i < _Size; i++)
				_Alloc.destroy(_Ptr + i);

			_Alloc.deallocate(_Ptr, _Capacity);
		}
		vector &operator = (const vector & other) {
			if (_Capacity)
				clear();

			insert(begin(),other.begin(),other.end());
			return *this;
		}

		iterator begin(){
			return _Ptr;
		}
		const_iterator begin() const {
			return _Ptr;
		}
		iterator end(){
			return begin() + _Size;
		} 
		const_iterator end() const {
			return begin() + _Size;
		}
		reverse_iterator rbegin(){ 
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const {
			return reverse_iterator(end());
		}
		reverse_iterator rend(){
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const {
			return reverse_iterator(begin());
		}
		size_type size() const {
			return _Size;
		}
		size_type max_size() const {
			return _Alloc.max_size();
		}
		iterator erase (iterator position) {
			return (erase(position, position + 1));
		}
		const_iterator erase (iterator position) const {
			return (erase(position, position + 1));
		}
		iterator erase (iterator first, iterator last) {
			if (last <= first)
				return last;

			difference_type dist = last - first;
			for (iterator i = first; i != last; i++)
				_Alloc.destroy(i.operator->());
			for (iterator i = last; i != end(); i++ ) {
				_Alloc.construct((i - dist).operator->(), *i);  
				_Alloc.destroy(i.operator->());					
			}

			_Size -= dist;
			return first;
		}
		void reserve (size_type n) {
			if (n <= _Capacity || n == 0)
				return;

			pointer _Ptr = _Alloc.allocate(n);
			for (size_type i = 0; i < _Size; i++) {
				_Alloc.construct(_Ptr + i, this->_Ptr[i]); 
			}
			this->~ vector();
			this->_Ptr = _Ptr;
			_Capacity = n;
		}
		size_type capacity() const {
			return _Capacity;
		}
		bool empty() const {
			return _Size == 0;
		}
		reference operator[](size_type position) {
			return *(_Ptr + position);
		}
		const_reference operator[](size_type position) const {
			return *(_Ptr + position);
		}
		reference at(size_type position) { 
			if (position < 0 || position >= size())
   				throw std::out_of_range("Out of range");

			return *(_Ptr + position);
		}
		const_reference at(size_type position) const {
			if (position < 0 || position >= size())
   				throw std::out_of_range("Out of range");

			return *(_Ptr + position);
		}
		reference front() {
			return *begin();
		}
		const_reference front() const {
			return *begin();
		}
		reference back() {
			return *(end() - 1);
		}
		const_reference back() const {
			return *(end() - 1);
		}
		void	assign(size_type n, const value_type &val)
        {
            if (n)
            {
                clear();
                reserve(n);
                for (size_type i = 0; i < n; i++)
                    this->_Ptr[i] = val;
            }
			_Size = n;
        }
		
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
			difference_type n = 0;

			for (InputIterator i = first; i != last; i++)
				n++;
			if (n)
			{
				clear();
				reserve(n);
				for (difference_type i = 0; i < n; i++, first++)
					this->_Ptr[i] = *first;
			}
			_Size = n;
		}
		void push_back(const value_type & value){
			insert(end(), value);
		}
		void pop_back(){
			erase(end() - 1);
		}
		iterator insert (iterator position, const value_type& val){
			difference_type move = position - begin();
			size_type n = 1;

			if (_Capacity < _Size + n)
			reserve(std::max(_Size * 2, _Size + n));
			position = begin() + move;
			for (iterator ptr = end() + n - 1; ptr >= position + n; ptr--) {
				_Alloc.construct(ptr.base(), *(ptr - n));
				_Alloc.destroy(ptr.base() - n);
			}
			for (iterator ptr = position + n - 1; ptr >= position; --ptr)
				_Alloc.construct(ptr.base(), val);
			_Size += n;

			return position;
		}
		void insert (iterator position, size_type n, const value_type& val){
			difference_type move = position - begin();

			if (n == 0 || move < 0)
				return;
			if (_Capacity < _Size + n)
			reserve(std::max(_Size * 2, _Size + n));
			position = begin() + move;
			for (iterator ptr = end() + n - 1; ptr >= position + n; ptr--)
			{
				_Alloc.construct(ptr.base(), *(ptr - n));
				_Alloc.destroy(ptr.base() - n);
			}
			for (iterator ptr = position + n - 1; ptr >= position; --ptr)
				_Alloc.construct(ptr.base(), val);
			_Size += n;
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator f, InputIterator l, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
			vector<T> vec(f, l);
			iterator first = vec.begin();
			iterator last = vec.end();
			difference_type dist = 0;
			difference_type pos = position - begin();

			for (iterator i = first; i != last; i++)
				dist++;
			if (_Capacity < _Size + dist)
				reserve(std::max(_Size * 2, _Size + dist));
			position = begin() + pos;
			for (iterator ptr = _Ptr + dist + _Size - 1; ptr >= position + dist; ptr--)
				{
					_Alloc.construct(ptr.base(), *(ptr - dist));
					_Alloc.destroy(ptr.base() - dist);
				}
			for (iterator ptr = position ; ptr != position + dist; ptr++, first++)
				_Alloc.construct(ptr.base(), *first);
			_Size += dist;
		}
		void swap(vector<T> & y){
			ft::swap(_Alloc, y._Alloc);
			ft::swap(_Ptr, y._Ptr);
			ft::swap(_Size, y._Size);
			ft::swap(_Capacity, y._Capacity);
		}
		void clear(){
			erase(begin(),end());
			_Size = 0;
		}
		void resize (size_type n, value_type val = value_type())
		{
			if (n >= _Size)
				insert(end(), n - _Size,val);
			else
				erase(begin() + n, end());
		}

	};

	/*NON MEM_FUNC*/
	template <typename T>
	void swap (ft::vector<T> & x, ft::vector<T>& y) {
		x.swap(y);
	}

	template <class T, class Alloc>
	bool operator== (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (false);

		typename ft::vector<T>::const_iterator first1 = lhs.begin();
		typename ft::vector<T>::const_iterator first2 = rhs.begin();
		while (first1 != lhs.end())
		{
			if (first2 == rhs.end() || *first1 != *first2)
				return (false);
			++first1;
			++first2;
		}

		return (true);
	}
	
	template <class T, class Alloc>
	bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return (!(rhs == lhs));
	}
	
	template <class T, class Alloc>
	bool operator< (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	
	template <class T, class Alloc>
	bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return (!(rhs < lhs));
	}
	
	template <class T, class Alloc>
	bool operator>  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return (rhs < lhs);
	}
	
	template <class T, class Alloc>
	bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return (!(lhs < rhs));
	}
	
}
