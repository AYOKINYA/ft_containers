#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>

namespace ft
{
	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1	first_argument_type;
		typedef Arg2	second_argument_type;
		typedef Result	result_type;
	};
	
	template <class T>
	struct less : binary_function < T , T , bool>
	{
  		bool operator() (const T& x, const T& y) const 
		{
			return (x < y);
		}
	};

	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() {};
		template <class U, class V>
		pair (const pair<U, V> &pr) : first(pr.first), second(pr.second) {};
		pair (const first_type& a, const second_type& b) : first(a), second(b) {};
		pair<T1, T2>& operator= (const pair<T1, T2>& pr)
		{
			if (this == &pr)
				return (*this);
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}
		template <typename U, typename V>
		pair<T1, T2>& operator= (const pair<U, V>& pr)
		{
			// if (this == &pr)
			// 	return (*this);
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template <class T1, class T2>
  	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return !(lhs==rhs);
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	}

	// 윗부분은 그냥 std::에서 불러와서 쓰면 되지만 공부할 겸 만들었다.

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <typename Iterator>
	class ReverseIterator
	{
		private:
				Iterator base_;
		public:
				typedef Iterator iterator_type;
				typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
				typedef typename iterator_traits<Iterator>::value_type			value_type;
				typedef typename iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename iterator_traits<Iterator>::pointer				pointer;
				typedef typename iterator_traits<Iterator>::reference			reference;

				ReverseIterator() : base_(nullptr) {};
				~ReverseIterator() {};
				ReverseIterator(const ReverseIterator<Iterator> &copy)
				{
					*this = copy;
				};

				ReverseIterator(Iterator base) : base_(base)
				{};
				
				ReverseIterator<Iterator>& operator=(const ReverseIterator<Iterator> &rhs)
				{
					if (this == &rhs)
						return (*this);
					this->base_ = rhs.base_;
					return (*this);
				}

				Iterator base() const
				{
					return (this->base_);
				}

				reference operator*(void) const
				{
					Iterator tmp(base_);
					--tmp;
					return (*tmp);
				}

				ReverseIterator<Iterator> operator+(difference_type n) const
				{
					return (base_ - n);
				}

				ReverseIterator<Iterator>& operator++()
				{
					--base_;
					return (*this);
				}

				ReverseIterator<Iterator> operator++(int)
				{
					ReverseIterator<Iterator> ite(base_--);
					return (ite);
				}

				ReverseIterator<Iterator>& operator+=(difference_type n)
				{
					//base_ -= n;
					while (n--)
						--base_;

					return (*this);
				}

				ReverseIterator<Iterator> operator-(difference_type n) const
				{
					return (base_ + n);
				}

				ReverseIterator<Iterator>& operator--()
				{
					++base_;
					return (*this);
				}

				ReverseIterator<Iterator> operator--(int)
				{
					ReverseIterator<Iterator> ite(base_++);
					return (ite);
				}

				ReverseIterator<Iterator>& operator-=(difference_type n)
				{
					// base_ += n;
					while (n--)
						++base_;
					
					return (*this);
				}

				pointer operator->() const
				{
					return (&(operator*()));
				}

				reference operator[] (difference_type n) const
				{
					return (this->base()[-n - 1]);
				}

	};

	template <class Iterator>
 	bool operator== (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator>
	bool operator!= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class Iterator>
	bool operator<  (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class Iterator>
	bool operator<= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator>
	bool operator>  (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class Iterator>
	bool operator>= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template <typename Iterator>
	ReverseIterator<Iterator> operator+(typename ReverseIterator<Iterator>::difference_type n,
											const ReverseIterator<Iterator>& rev_it)
	{
		ReverseIterator<Iterator> res(rev_it.base() - n);
		return (res);
	}

	template <typename Iterator>
	ReverseIterator<Iterator> operator-(typename ReverseIterator<Iterator>::difference_type n,
											const ReverseIterator<Iterator>& rev_it)
	{
		ReverseIterator<Iterator> res(rev_it.base() + n);
		return (res);
	}

};

#endif