#pragma once

#include "../utils.hpp"
#include "../iterators/reverse_iterator.hpp"
#include <cstdlib>
#include <iterator>
#include "rbtree.hpp"
#include <limits>

namespace ft {
	template < class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key,T> > >
	class map {
	public:
		typedef Key										key_type;
		typedef T 										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;

		class value_compare
		{
			friend class map;
			protected:
			Compare _Cmp;
			value_compare (Compare c) : _Cmp(c) {} 
			public:
			typedef bool								result_type;
			typedef value_type							first_argument_type;
			typedef value_type							second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return _Cmp(x.first, y.first);
			}
		};

		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;
		typedef rbtree_iterator<value_type>					iterator;
		typedef rbtree_const_iterator<value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		allocator_type										_Alloc;
		ft::rbtree<ft::pair<const Key, T>, value_compare>	_Tree;
		key_compare											_Cmp;

		static bool keys_equal(const ft::pair<const Key, T> &left, const ft::pair<const Key, T> &right) {
			Compare _Cmp;
			
			return !(_Cmp(left.first, right.first) || _Cmp(right.first, left.first));
		}
		static bool key_gr_eq(const ft::pair<const Key, T> &left, const ft::pair<const Key, T> &right) {
			Compare _Cmp;
			
			return (!_Cmp(right.first, left.first));
		}
		static bool key_sm(const ft::pair<const Key, T> &left, const ft::pair<const Key, T> &right ){
			Compare _Cmp;
			
			return _Cmp(left.first, right.first);
		}

	public:
		explicit map (const key_compare& _Cmp = key_compare(), const allocator_type& alloc = allocator_type()): _Alloc(alloc), _Tree(value_compare(_Cmp)), _Cmp(_Cmp) {}
		
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& _Cmp = key_compare(), const allocator_type& alloc = allocator_type()): _Alloc(alloc), _Tree(first, last, value_compare(_Cmp)), _Cmp(_Cmp) {}
		map (const map& other): _Tree(other._Tree){}
		~map(){}
		
		iterator begin() {
			return _Tree.begin();
		}
		const_iterator begin() const {
			return _Tree.begin();
		}
		iterator end() {
			return _Tree.end();
		}
		const_iterator end() const {
			return _Tree.end();
		}
		reverse_iterator rbegin() {
			return _Tree.rbegin();
		}
		const_reverse_iterator rbegin() const {
			return _Tree.rbegin();
		}
		reverse_iterator rend() {
			return _Tree.rend();
		}
		const_reverse_iterator rend() const {
			return _Tree.rend();
		}

		bool empty() const {
			return _Tree.empty();
		}
		size_type size() const {
			return _Tree.size();
		}
		size_type max_size() const {
			return _Tree.max_size();
		}
			
		map& operator= (const map& other){
			_Tree.operator=(other._Tree);
			return (*this);
		}

		mapped_type &operator[] (const key_type& k) { return ((insert(ft::make_pair<key_type, mapped_type>(k, mapped_type()))).first).base()->data.second;}
		pair<iterator,bool> insert (const value_type& val)
		{
			size_type length_before = size();
			iterator it = _Tree.insert(val);
			bool elementInserted = size() > length_before;
			return ft::make_pair<iterator, bool>(it, elementInserted);
		}
		iterator insert (iterator position, const value_type& val)
		{ return _Tree.insert(position, val);}
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last){ _Tree.insert(first, last);}
		void erase (iterator position){ _Tree.erase(position);}
		size_type erase (const key_type& k) {return _Tree.eraseIf(keys_equal, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
		void erase (iterator first, iterator last) {_Tree.erase(first, last);}
		void swap (map& x) {_Tree.swap(x._Tree);}
		void clear() {_Tree.clear();}
		key_compare key_comp() const {return key_compare();}
		value_compare value_comp() const {return value_compare(Compare());}
		iterator find (const key_type& k) {return _Tree.find(keys_equal, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
		const_iterator find (const key_type& k) const {return _Tree.find(keys_equal, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
		size_type count (const key_type& k) const {return _Tree.countIf(keys_equal, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
		iterator lower_bound (const key_type& k) {return _Tree.find(key_gr_eq, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
		const_iterator lower_bound (const key_type& k) const {return _Tree.find(key_gr_eq, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
		iterator upper_bound (const key_type& k) {return _Tree.find(key_sm, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
		const_iterator upper_bound (const key_type& k) const {return _Tree.find(key_sm, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const {return ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));}
		pair<iterator,iterator> equal_range (const key_type& k) {return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));}
	};
	template <class Key, class T, class Compare, class Allocator>
	bool	operator==(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool	operator!=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs) {
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool	operator< (const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Allocator>
	bool	operator<=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs) {
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool	operator> (const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs) {
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool	operator>=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs) {
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Allocator>
	void	swap(map<Key, T, Compare, Allocator> &x, map<Key, T, Compare, Allocator> &y) {
		x.swap(y);
	}

}
