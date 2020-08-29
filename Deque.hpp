#ifndef DEQUE_HPP
# define DEQUE_HPP

# include "Iterator.hpp"
# include "List.hpp"
namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class Deque
	{
		private:
				List<T, Alloc> list_;
		public:
				typedef T 								value_type;
				typedef Alloc							allocator_type;
				typedef size_t							size_type;
				typedef std::ptrdiff_t					difference_type;
				typedef typename Alloc::reference		reference;
				typedef typename Alloc::const_reference	const_reference;
				typedef typename Alloc::pointer			pointer;
				typedef typename Alloc::const_pointer	const_pointer;
				typedef IteratorList<T> 				iterator;
				typedef IteratorList<const T>			const_iterator;
				typedef ReverseIterator<iterator>		reverse_iterator;
				typedef ReverseIterator<const_iterator>	const_reverse_iterator;

				explicit Deque() : list_()
				{};
		
				explicit Deque(size_type n, const value_type& val = value_type())
				:	list_(n, val)
				{};
					
				template <class InputIterator>
				Deque(InputIterator first, InputIterator last)
				:	list_(first, last)
				{};
					
				Deque(const Deque& x) : list_(x.list_)
				{};

				Deque& operator=(const Deque &copy)
				{
					if (this == &copy)
						return (*this);
					this->list_ = copy.list_;
					return (*this);
				}
				
				iterator 		begin(void)
				{
					return (list_.begin());
				}

				const_iterator 		begin(void) const
				{
					return (list_.begin());
				}

				iterator 		end(void)
				{
					return (list_.end());
				}

				const_iterator	end(void) const
				{
					return (list_.end());
				}

				reverse_iterator 		rbegin(void)
				{
					return (list_.rbegin());
				}

				const_reverse_iterator	rbegin(void) const
				{
					return (list_.rbegin());
				}

				reverse_iterator 		rend(void)
				{
					return (list_.rend());			
				}

				const_reverse_iterator	rend(void) const
				{
					return (list_.rend());
				}

				size_type size() const
				{
					return (list_.size());
				}

				size_type max_size() const
				{
					return (list_.max_size());
				}

				void	resize (size_type n, value_type val = value_type())
				{
					list_.resize(n, val);
				}

				bool	empty() const
				{
					return (list_.empty());
				}

				reference operator[] (size_type n)
				{
					iterator ret = list_.begin();
					while (n)
					{
						++ret;
						--n;
					}
					return (ret.getPtr()->data);
				}
				const_reference operator[] (size_type n) const
				{
					iterator ret = list_.begin();
					while (n)
					{
						++ret;
						--n;
					}
					return (ret.getPtr()->data);
				}
				reference front()
				{
					return (list_.front());
				}
				reference at (size_type n)
				{
					if (n >= list_.size())
						throw std::out_of_range("ft::Deque : The index is out of range!");
					
					iterator ret = list_.begin();
					while (n)
					{
						++ret;
						--n;
					}
					return (ret.getPtr()->data);
				}
				const_reference at (size_type n) const
				{
					if (n >= list_.size())
						throw std::out_of_range("ft::Deque : The index is out of range!");
					
					iterator ret = list_.begin();
					while (n)
					{
						++ret;
						--n;
					}
					return (ret.getPtr()->data);
				}
				const_reference front() const
				{
					return (list_.front());
				}
				reference			back(void)
				{
					return (list_.back());
				}

				const_reference		back(void) const
				{
					return (list_.back());
				}
				template <typename InputIt>
				void assign(InputIt first, InputIt last)
				{
					list_.assign(first, last);
				}
				void assign(size_type n, const value_type& val)
				{
					list_.assign(n, val);
				}
				void push_back (const value_type& val)
				{
					list_.push_back(val);
				}
				void push_front (const value_type& val)
				{
					list_.push_front(val);
				}
				void pop_back()
				{
					list_.pop_back();
				}
				void pop_front()
				{
					list_.pop_front();
				}
				iterator insert (iterator position, const value_type& val)
				{
					list_.insert(position, val);
				}
	
				void insert (iterator position, size_type n, const value_type& val)
				{
					list_.insert(position, n, val);
				}

				template <class InputIterator>
				void insert (iterator position, InputIterator first, InputIterator last)
				{
					list_.insert(position, first, last);
				}
				iterator erase (iterator position)
				{
					list_.erase(position);
				}
				iterator erase (iterator first, iterator last)
				{
					list_.erase(first, last);
				}
				void swap (Deque& x)
				{
					list_.swap(x.list_);
				}
				void clear()
				{
					list_.clear();
				}

		friend bool operator== (const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
		{
			return (lhs.list_ == rhs.list_);
		}
		friend bool operator!= (const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
		{
			return (lhs.list_ != rhs.list_);
		}

		friend bool operator> (const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
		{
			return (lhs.list_ > rhs.list_);
		}

		friend bool operator< (const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
		{
			return (lhs.list_ < rhs.list_);
		}
	};
	

	template <class T, class Alloc>
	bool operator>= (const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	bool operator<= (const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
	{
		return (!(lhs > rhs));
	}

	template <class T, class Alloc>
  	void swap (Deque<T, Alloc>& x, Deque<T, Alloc>& y)
	{
		x.swap(y);
	}

};

#endif