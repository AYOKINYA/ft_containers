#ifndef LIST_HPP
# define LIST_HPP
# include <memory>
# include <cstddef>
# include "Iterator.hpp"

namespace ft
{
	template <typedef T>
	struct t_node
	{
		T		data;
		t_list	*prev;
		t_list	*next;
	};

	template <typedef T, typdef Category = bidirectional_iterator_flag>
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
				IteratorList(t_list<T> *list)
				{
					this->ptr = list;
				};

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

	template <typename T, typename Allocator = std::allocator<T>>
	class List
	{
		private:
				unsigned int		size;
				t_node<T>			*head;
				t_node<T>			*tail;

		public:
				List();
				~List();
				List(const List<T> &copy);
				List<T>& operator=(const List<T> &list);

				typedef typename T value_type;
				typedef typename Allocator allocator_type;
				typedef typename std::size_t size_type;
				typedef typename std::ptrdiff_t difference_type;
				typedef typename Allocator::reference reference;
				typedef typename Allocator::const_reference const_reference;
				typedef typename Allocator::pointer pointer;
				typedef typename Allocator::const_pointer const_pointer;
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

				// template <typename InputIt>
				// void assign(InputIt first, InputIt last);
				// void assign(size_type n, const value_type& val);
				iterator insert (iterator position, const value_type& val);
				void insert (iterator position, size_type n, const value_type& val);
				template <class InputIterator>
				void insert (iterator position, InputIterator first, InputIterator last);

				void	push_back(const value_type&elem);
				void	pop_back(void);
				void	push_front(const value_typ&elem);
				void	pop_front(void);

	};
}

#endif