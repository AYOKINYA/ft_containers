#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>

namespace ft
{
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