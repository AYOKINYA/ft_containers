#ifndef LIST_HPP
# define LIST_HPP
# include <memory>
# include <cstddef>
# include "Iterator.hpp"

namespace ft
{
	template <typename T>
	struct t_node
	{
		t_list	*prev;
		t_list	*next;
		T		data;
	};

	template <typename T, typename Category = bidirectional_iterator_flag>
	class IteratorList
	{
		private:

		protected:
				t_list<T> *ptr;
		public:
				typedef T				value_type;
				typedef std::ptrdiff_t	difference_type;
				typedef T*				pointer;
				typedef T&				reference;
				typdef Category			category;

				IteratorList() {};
				~IteratorList() {};
				IteratorList(t_list<T> *list) : ptr(list) {};

				IteratorList(const IteratorList &copy)
				{
					*this = copy;
				}

				IteratorList& operator=(const IteratorList &rhs)
				{
					if (this == &rhs)
						return (*this);

					this->ptr = rhs->ptr;

					return (*this);
				}

				IteratorList &operator++(void)
				{
					if (this->ptr && this->ptr->next)
						this->ptr = this->ptr->next;
					return (*this);
				}

				IteratorList operator++ (int)
				{
					IteratorList tmp(*this);
					this->operator++();
					return (tmp);
				}
				
				IteratorList &operator--(void)
				{
					if (this->ptr && this->ptr->prev)
						this->ptr = this->ptr->prev;
					return (*this);
				}

				IteratorList operator-- (int)
				{
					IteratorList tmp(*this);
					this->operator--();
					return (tmp);
				}

				bool operator==(const IteratorList &rhs) const
				{
					return (this->ptr == rhs->ptr);
				}

				bool operator!=(const IteratorList &rhs) const
				{
					return (this->ptr != rhs->ptr);
				}

				T& operator*(void)
				{
					return (this->ptr->data);
				}

				T* operator->(void)
				{
					return (&(this->ptr->data));
				}

				t_list<T>	*getPtr(void)
				{
					return (this->ptr);
				}
	};

	template <typename T, typename Alloc = std::allocator<T>>
	class List
	{
		private:
				unsigned int		size;
				t_node<T>			*head;
				t_node<T>			*tail;

				t_node<T>			*begin_;
				t_node<T>			*end_;

		public:
				explicit List (const allocator_type& alloc = allocator_type());
				explicit List (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
				template <class InputIterator>
				List (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
				List(const List<T> &copy);
				~List();
				List<T>& operator=(const List<T> &list);

				typedef typename T value_type;
				typedef typename Alloc allocator_type;
				typedef typename std::size_t size_type;
				typedef typename std::ptrdiff_t difference_type;
				typedef typename Alloc::reference reference;
				typedef typename Alloc::const_reference const_reference;
				typedef typename Alloc::pointer pointer;
				typedef typename Alloc::const_pointer const_pointer;
				typedef typename IteratorList<T> iterator;
				typedef typename IteratorList<const T> const_iterator;
				typedef typename ReverseIterator<Iterator> reverse_iterator;
				typedef typename ReverseIterator<const Iterator> const_reverse_iterator;

				iterator 		begin(void);
				const_iterator	begin(void);
				iterator 		end(void);
				const_iterator	end(void);
				reverse_iterator 		rbegin(void);
				const_reverse_iterator	rbegin(void);
				reverse_iterator 		rend(void);
				const_reverse_iterator	rend(void);

				bool	empty() const;
				size_type size() const;
				size_type max_size() const;
				
				reference			front(void);
				const_reference		front(void) const;
				reference			back(void);
				const_reference		back(void) const;

				template <typename InputIt>
				void assign(InputIt first, InputIt last);
				void assign(size_type n, const value_type& val);
				iterator insert (iterator position, const value_type& val);
				void insert (iterator position, size_type n, const value_type& val);
				template <class InputIterator>
				void insert (iterator position, InputIterator first, InputIterator last);

				iterator erase (iterator position);
				iterator erase (iterator first, iterator last);

				void	swap (list& x);

				void	resize (size_type n, value_type val = value_type());

				void	clear();

				void	splice (iterator position, list& x);
				void	splice (iterator position, list& x, iterator i);
				void	splice (iterator position, list& x, iterator first, iterator last);		
				void	remove (const value_type& val);
				template <typename Predicate>
  				void	remove_if (Predicate pred);

				void	unique();
				template <typename BinaryPredicate>
  				void	unique (BinaryPredicate binary_pred);
				
				void	merge (list& x);
				template <typename Compare>
  				void	merge (list& x, Compare comp);

				void	sort();
				template <typename Compare>
 				void	sort (Compare comp);

				void	reverse();

				void	push_back(const value_type & val);
				void	pop_back(void);
				void	push_front(const value_type & val);
				void	pop_front(void);

				template <typename E>
				friend class ListItertor;
	};

	template <class T, class Alloc>
	bool operator== (const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (0);
		else
		{
			typename List<T, Alloc>::iterator l_iter = lhs.begin();
			typename List<T, Alloc>::iterator r_iter = rhs.begin();
			for (unsigned int i = 0; i < lhs.size(); ++i)
			{
				if (*l_iter != *r_iter)
					return (0);
				++l_iter;
				++r_iter;
			}
		}
		return (1);
	}

	template <class T, class Alloc>
	bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (!(lhs == rhs))
	}

	template <class T, class Alloc>
	bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		unsigned int n;

		if (lhs.size() < rhs.size())
			n = lhs.size();
		else
			n = rhs.size();

		typename List<T, Alloc>::iterator l_iter = lhs.begin();
		typename List<T, Alloc>::iterator r_iter = rhs.begin();

		for (unsigned int i = 0; i < n; ++i)
		{
			if (*l_iter != *r_iter)
				return (*l_iter < *r_iter);
			++l_iter;
			++r_iter;
		}

		return (lhs.size() < rhs.size());
	}

	template <class T, class Alloc>
	bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
  	void swap (list<T, Alloc>& x, list<T, Alloc>& y)
	{
		x.swap(y);
	}
};

#endif