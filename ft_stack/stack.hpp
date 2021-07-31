#pragma once

#include "../ft_vector/vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack {
	public:
		typedef Container							container_type;
		typedef typename container_type::value_type	value_type;
		typedef typename container_type::size_type	size_type;
		
	protected:
		container_type _Cntnr;
	
	public:
		explicit stack (const container_type& ctnr = container_type()) : _Cntnr(ctnr) {}
		~stack() {}

		bool				empty() const {
			return (this->_Cntnr.empty());
		}
		
		size_type			size() const {
			return (this->_Cntnr.size());
		}

		value_type&			top() {
			return (this->_Cntnr.back());
		}

		const value_type&	top() const {
			return (this->_Cntnr.back());
		}
		void				push(const value_type& val) {
			this->_Cntnr.push_back(val);
		}
		void				pop() {
			this->_Cntnr.pop_back();
		}
		
		template <class TT, class ContainerT>
		friend bool operator== (const ft::stack<TT, ContainerT>& left, const ft::stack<TT, ContainerT>& right);

		template <class TT, class ContainerT>
		friend bool operator!= (const ft::stack<TT, ContainerT>& left, const ft::stack<TT, ContainerT>& right);

		template <class TT, class ContainerT>
		friend bool operator< (const ft::stack<TT, ContainerT>& left, const ft::stack<TT, ContainerT>& right);

		template <class TT, class ContainerT>
		friend bool operator<= (const ft::stack<TT, ContainerT>& left, const ft::stack<TT, ContainerT>& right);

		template <class TT, class ContainerT>
		friend bool operator> (const ft::stack<TT, ContainerT>& left, const ft::stack<TT, ContainerT>& right);

		template <class TT, class ContainerT>
		friend bool operator>= (const ft::stack<TT, ContainerT>& left, const ft::stack<TT, ContainerT>& right);

	};
	template <class T, class Container>
	bool operator== (const ft::stack<T, Container>& left, const ft::stack<T, Container>& right) {
		return (left._Cntnr == right._Cntnr);
	}
	
	template <class T, class Container>
	bool operator!= (const ft::stack<T, Container>& left, const ft::stack<T, Container>& right) {
		return (left._Cntnr != right._Cntnr);
	}
	
	template <class T, class Container>
	bool operator< (const ft::stack<T, Container>& left, const ft::stack<T, Container>& right) {
		return (left._Cntnr < right._Cntnr);
	}
	
	template <class T, class Container>
	bool operator<= (const ft::stack<T, Container>& left, const ft::stack<T, Container>& right) {
		return (left._Cntnr <= right._Cntnr);
	}
	
	template <class T, class Container>
	bool operator> (const ft::stack<T, Container>& left, const ft::stack<T, Container>& right) {
		return (left._Cntnr > right._Cntnr);
	}
	
	template <class T, class Container>
	bool operator>= (const ft::stack<T, Container>& left, const ft::stack<T, Container>& right) {
		return (left._Cntnr >= right._Cntnr);
	}
}