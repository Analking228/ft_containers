#pragma once

namespace ft {
template < class iterator >
class	reverse_iterator
{
	public:
		typedef	iterator								iterator_type;
		typedef	typename iterator::iterator_category	iterator_category;
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::pointer				pointer;
		typedef typename iterator::reference			reference;

	private:
		iterator_type									_It;

	public:
		reverse_iterator(): _It() {}
		reverse_iterator(const iterator_type & other) :  _It(other) {}
		template <typename Iter>
		reverse_iterator(const reverse_iterator< Iter >  & src): _It(src.base()) {}

		iterator_type									base() const	{
			return (this->_It);
		}
		reverse_iterator&								operator++() {
			(this->_It)--;
			return (*this);
		}
		reverse_iterator								operator++(int) {
			reverse_iterator result(*this); this->operator++();
			return (result);
		}
		reverse_iterator&								operator--() {
			(this->_It)++; return (*this);
		}
		reverse_iterator								operator--(int) {
			reverse_iterator result(*this);
			this->operator--();
			return (result);
		}
		reverse_iterator								operator+(difference_type n) const {
			return (reverse_iterator(this->_It - n));
		}
		reverse_iterator								operator-(difference_type n) const {
			return (reverse_iterator(this->_It + n));
		}
		reverse_iterator&								operator+=(difference_type n) {
			(this->_It) -= n; return (*this);
		}
		reverse_iterator&								operator-=(difference_type n) {
			(this->_It) += n; return (*this);
		}
		bool											operator==(reverse_iterator const & rhs) const {
			return (this->_It == rhs._It);
		}
		bool											operator!=(reverse_iterator const & rhs) const {
			return (this->_It != rhs._It);
		}

		reference										operator*() const {
			iterator tmp = _It; return *--tmp;
		}
		pointer											operator->() const {
			return (&(this->operator*()));
		}
		reference										operator[](difference_type n) const {
			return base()[-n-1];
		}
	};
	
	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
		return (rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() - rhs.base());
	}
	
	template <class Iterator_L, class Iterator_R>
	typename reverse_iterator<Iterator_L>::difference_type operator- (const reverse_iterator<Iterator_L>& lhs,const reverse_iterator<Iterator_R>& rhs) {
		return (rhs.base() - lhs.base());
	}
	
	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator== (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator!= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator< (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator<= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator> (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) {
		return (lhs.base() < rhs.base());
	}
    
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator>= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) {
		return (lhs.base() <= rhs.base());
	}
}
