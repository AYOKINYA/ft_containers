#ifndef LIST_HPP
# define LIST_HPP
# include <memory>
# include <cstddef>
# include <limits>
# include "Iterator.hpp"
# include <iostream>

namespace ft
{
	template <typename T>
	struct t_node
	{
		t_node<T>	*prev;
		t_node<T>	*next;
		T			data;
	};

	/*
	**	Iterator class for ft::List<T>
	*/

	template <typename T, typename Category = bidirectional_iterator_tag>
	class IteratorList
	{
		private:
				t_node<T>					*ptr;
		public:
				typedef T					value_type;
				typedef std::ptrdiff_t		difference_type;
				typedef T*					pointer;
				typedef T&					reference;
				typedef Category			iterator_category;

				IteratorList() {};
				~IteratorList() {};
				IteratorList(t_node<T> *List) : ptr(List) {};

				IteratorList(const IteratorList &copy)
				{
					*this = copy;
				}

				IteratorList& operator=(const IteratorList &rhs)
				{
					if (this == &rhs)
						return (*this);

					this->ptr = rhs.ptr;

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
					return (this->ptr == rhs.ptr);
				}

				bool operator!=(const IteratorList &rhs) const
				{
					return (this->ptr != rhs.ptr);
				}

				T& operator*(void)
				{
					return (this->ptr->data);
				}

				T* operator->(void)
				{
					return (&(this->ptr->data));
				}

				t_node<T>	*getPtr(void)
				{
					return (this->ptr);
				}
	};

	template <typename T, typename Alloc = std::allocator<T> >
	class List
	{
		private:
				unsigned int		length;
				t_node<T>			*head;
				t_node<T>			*tail;

				t_node<T>			*end_;

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
				typedef ReverseIterator<const iterator>	const_reverse_iterator;


				explicit List()
					: length(0), head(nullptr), tail(nullptr), end_(nullptr)
				{
					this->end_ = new t_node<T>();
					this->end_->next = nullptr;
					this->end_->prev = this->tail;
					this->end_->data = 0;
					
				}

				explicit List(size_type n, const value_type& val = value_type())
					: length(0), head(nullptr), tail(nullptr), end_(nullptr)
				{

					this->end_ = new t_node<T>();
					this->end_->next = nullptr;
					this->end_->prev = this->tail;
					this->end_->data = 0;

					insert(begin(), n, val);
				}

				template <class InputIterator>
				List(InputIterator first, InputIterator last)
					: length(0), head(nullptr), tail(nullptr), end_(nullptr)
				{
					this->end_ = new t_node<T>();
					this->end_->next = nullptr;
					this->end_->prev = this->tail;
					this->end_->data = 0;
					
					insert(begin(), first, last);
				}

				List(const List<T> &copy): length(0), head(nullptr), tail(nullptr), end_(nullptr)
				{
					*this = copy;
				}

				~List()
				{
					
					if (this->length)
						clear();
					if (this->end_)
						delete (this->end_);
				}

				List<T>& operator=(const List<T> &List)
				{
					if (this == &List)
						return (*this);
					
					if (this->length)
						clear();
					if (this->end_)
						delete (this->end_);
	
					this->end_ = new t_node<T>();
					this->end_->next = nullptr;
					this->end_->prev = List.end_->prev;
					this->end_->data = 0;
					
					insert(begin(), List.begin(), List.end());
					this->end_->prev = this->tail;
					return (*this);
				}

				/*
				**	iterators
				*/

				iterator 		begin(void)
				{
					return (iterator(this->head));
				}

				const_iterator	begin(void) const
				{
					return (const_iterator((t_node<const T>*)this->head));
				}

				iterator 		end(void)
				{
					return (iterator(this->end_));
				}

				const_iterator	end(void) const
				{
					return (const_iterator((t_node<const T>*)this->end_));
				}

				reverse_iterator 		rbegin(void)
				{
					return (reverse_iterator(end()));
				}

				const_reverse_iterator	rbegin(void) const
				{
					return (const_reverse_iterator(end()));
				}

				reverse_iterator 		rend(void)
				{
					return (reverse_iterator(begin()));			
				}

				const_reverse_iterator	rend(void) const
				{
					return (const_reverse_iterator(begin()));
				}

				/*
				**	capacity
				*/

				bool	empty() const
				{
					return (this->length == 0);
				}

				size_type size() const
				{
					return (this->length);
				}

				size_type max_size() const
				{
					return (std::numeric_limits<size_type>::max() / sizeof(this->head));
				}
				
				/*
				**	element access
				*/
				
				reference			front(void)
				{
					return (this->head->data);
				}

				const_reference		front(void) const
				{
					return (this->head->data);
				}

				reference			back(void)
				{
					return (this->tail->data);
				}

				const_reference		back(void) const
				{
					return (this->tail->data);
				}

				/*
				**	modifiers
				*/

				template <typename InputIt>
				void assign(InputIt first, InputIt last)
				{
					clear();
					insert(begin(), first, last);
				}
				void assign(size_type n, const value_type& val)
				{
					clear();
					insert(begin(), n, val);
				}

				iterator insert(iterator position, const value_type& val)
				{
					insert(position, (std::size_t)1, val);

					if (position == begin() || position == end() || position.getPtr() == nullptr)
						return (position);
					else
						return (iterator(position.getPtr()->prev));
				}

				void insert(iterator position, size_type n, const value_type& val)
				{
					t_node<T> *cur_node;
					t_node<T> *left_node;

					if (this->length == 0 && position != end())
					{
						cur_node = nullptr;
						left_node = nullptr;
					}
					else
					{
						cur_node = position.getPtr();
						if (cur_node == nullptr || begin().getPtr() == nullptr)
							left_node = nullptr;
						else
							left_node = position.getPtr()->prev;
					}
					
					for (unsigned int i = 0; i < n; i++)
					{
						t_node<T> *new_node = new t_node<T>();
						
						new_node->prev = left_node;
						new_node->next = nullptr;
						new_node->data = val;

						if (left_node)
							left_node->next = new_node;
						else
							this->head = new_node; 
						++this->length;
						left_node = new_node;
					}
					if (cur_node)
					{
						cur_node->prev = left_node;
						left_node->next = cur_node;
					}
					else
						this->tail = left_node;
					
					if (position == end())
						this->tail = left_node;
					this->tail->next = this->end_;
					this->end_->prev = this->tail;
				}

				template <class InputIterator>
				void insert (iterator position, InputIterator first, InputIterator last)
				{
					t_node<T> *cur_node;
					t_node<T> *left_node;

					if (this->length == 0 && position != end())
					{	
						cur_node = nullptr;
						left_node = nullptr;
					}
					else
					{
						cur_node = position.getPtr();
						if (cur_node == nullptr || begin().getPtr() == nullptr)
							left_node = nullptr;
						else
							left_node = position.getPtr()->prev;
					}
					
					for (InputIterator ite = first; ite != last; ++ite)
					{
						t_node<T> *new_node = new t_node<T>();
						
						new_node->prev = left_node;
						new_node->next = nullptr;
						new_node->data = *ite;

						if (left_node)
							left_node->next = new_node;
						else
							this->head = new_node; 
						++this->length;
						left_node = new_node;
					}

					if (cur_node)
					{
						cur_node->prev = left_node;
						left_node->next = cur_node;
					}
					else
						this->tail = left_node;
					
					if (position == end())
						this->tail = left_node;

					this->tail->next = this->end_;
					this->end_->prev = this->tail;
				}

				iterator erase (iterator position)
				{
					iterator tmp = iterator(position);
					++tmp;
					return (erase(position, tmp));
				}

				iterator erase (iterator first, iterator last)
				{
					if (this->length == 0 || first.getPtr() == nullptr)
						return (iterator(this->head));

					t_node<T> *left_node = first.getPtr()->prev;

					iterator ite = first;

					while (ite != last)
					{
						iterator tmp(ite);
						if (tmp.getPtr())
							delete (tmp.getPtr());
						--this->length;
						++ite;
					}
					
					if (this->length == 0)
					{
						this->head = nullptr;
						this->tail = nullptr;
					}
					else
					{
						if (left_node)
							left_node->next = last.getPtr();
						else
							this->head = last.getPtr();

						last.getPtr()->prev = left_node;

						if (last == end())
						{
							this->tail = left_node;
							left_node->next = last.getPtr();
						}			
					}

					return (last);
				}

				void	swap (List& x)
				{
					std::swap(this->head, x.head);
					std::swap(this->tail, x.tail);
					std::swap(this->length, x.length);
					std::swap(this->end_, x.end_);
				}

				void	resize (size_type n, value_type val = value_type())
				{
					while (this->length > n)
						this->pop_back();
					while (this->length < n)
						this->push_back(val);
				}

				void 	clear()
				{
					erase(begin(), end());
				}

				void	push_front(const value_type & val)
				{
					insert(begin(), val);
				}

				void	pop_front(void)
				{
					erase(begin());
				}

				void	push_back(const value_type& val)
				{
					insert(end(), val);
				}

				void	pop_back(void)
				{
					iterator iter = end();
					--iter;
					erase(iter);
				}

				/*
				**	operations
				*/

				void	splice (iterator position, List& x)
				{
					insert(position, x.begin(), x.end());
					x.clear();
				}

				void	splice (iterator position, List& x, iterator i)
				{
					insert(position, *i);
					x.erase(i);
				}

				void	splice (iterator position, List& x, iterator first, iterator last)
				{
					insert(position, first, last);
					x.erase(first, last);
				}

				void	remove (const value_type& val)
				{
					iterator iter = begin();
					while (iter != end())
					{
						if (*iter == val)
							iter = erase(iter);
						else
							++iter;
					}
				}

				template <typename Predicate>
				void	remove_if (Predicate pred)
				{
					iterator iter = begin();
					while (iter != end())
					{
						if (pred(*iter))
							iter = erase(iter);
						else
							++iter;
					}
				}

				void	unique()
				{
					if (this->length < 2)
						return ;

					iterator first;
					iterator second;
					iterator tmp;

					first = begin();
					while (first != end())
					{
						second = first;
						++second;
						while (second != end())
						{
							tmp = second;
							if (*first == *second)
							{
								erase(second);
								second = tmp;
							}
							++second;
						}
						++first;
					}
				}

				template <typename BinaryPredicate>
				void	unique (BinaryPredicate binary_pred)
				{
					if (this->length < 2)
						return ;

					iterator first;
					iterator second;
					iterator tmp;

					first = begin();
					while (first != end())
					{
						second = first;
						++second;
						while (second != end())
						{
							tmp = second;
							if (binary_pred(*first, *second))
							{
								erase(second);
								second = tmp;
							}
							++second;
						}
						++first;
					}
				}

				void	merge (List& x)
				{
					if (this == &x)
						return ;
					
					size_type size;
					iterator iter;
					iterator x_iter;
					iterator next;

					size = this->length;
					if (size)
						iter = this->begin();
					if (x.length)
						x_iter = x.begin();

					while (x.length)
					{
						while (size && (iter != end()) && !(*x_iter < *iter))
							++iter;
						next = x_iter;
						if (x.length != 1)
							++next;
						if (size && iter != end())
							splice(iter, x, x_iter);
						else
						{
							this->push_back(*x_iter);
							x.erase(x_iter);
						}
						x_iter = next;
					}
				}

				template <typename Compare>
				void	merge (List& x, Compare comp)
				{
					if (this == &x)
						return ;

					size_type size;
					iterator iter;
					iterator x_iter;
					iterator next;

					size = this->length;
					if (size)
						iter = this->begin();
					if (x.length)
						x_iter = x.begin();
					while (x.length)
					{
						while (size && (iter != end()) && !comp(*x_iter, *iter))
							++iter;
						next = x_iter;
						if (x.length != 1)
							++next;
						if (size && iter != end())
							splice(iter, x, x_iter);
						else
						{
							this->push_back(*x_iter);
							x.erase(x_iter);
						}
						x_iter = next;
					}
				}

				void	sort()
				{
					iterator first;
					iterator second;

					for (unsigned int i = 0; i < this->length ; ++i)
					{
						first = this->begin();
						second = first;
						++second;
						while (second != end())
						{
							if (*second < *first)
								splice(first, *this, second);
							else
								++first;
							second = first;
							++second;
						}
					}
				}

				template <typename Compare>
				void	sort(Compare comp)
				{
					iterator first;
					iterator second;

					for (unsigned int i = 0; i < this->length ; ++i)
					{
						first = this->begin();
						second = first;
						++second;
						while (second != end())
						{
							if (comp(*second, *first))
								splice(first, *this, second);
							else
								++first;
							second = first;
							++second;
						}
					}
				}

				void	reverse()
				{
					iterator start = this->begin();
					iterator last = this->end();
					--last;

					for (unsigned int i = 0; i < this->length / 2; ++i)
					{
						std::swap(*start, *last);
						++start;
						--last;
					}
				}

				template <typename E>
				friend class ListItertor;
	};

	/*
	**	non-member function overloads
	*/

	template <class T, class Alloc>
	bool operator== (const List<T, Alloc>& lhs, const List<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (0);
		else
		{
			typename List<T, Alloc>::const_iterator l_iter = lhs.begin();
			typename List<T, Alloc>::const_iterator r_iter = rhs.begin();
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
	bool operator!= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		unsigned int n;
		
		if (lhs.size() < rhs.size())
			n = lhs.size();
		else
			n = rhs.size();

		typename List<T, Alloc>::const_iterator l_iter = lhs.begin();
		typename List<T, Alloc>::const_iterator r_iter = rhs.begin();

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
	bool operator<= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
  	void swap (List<T, Alloc>& x, List<T, Alloc>& y)
	{
		x.swap(y);
	}
};

#endif