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

	template <typename T, typename Alloc = std::allocator<T>>
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
					
				}

				explicit List(size_type n, const value_type& val = value_type())
					: length(0), head(nullptr), tail(nullptr), end_(nullptr)
				{

					this->end_ = new t_node<T>();
					this->end_->next = nullptr;
					this->end_->prev = this->tail;

					insert(begin(), n, val);
				}

				template <class InputIterator>
				List(InputIterator first, InputIterator last)
					: length(0), head(nullptr), tail(nullptr), end_(nullptr)
				{
					this->end_ = new t_node<T>();
					this->end_->next = nullptr;
					this->end_->prev = this->tail;
					
					insert(begin(), first, last);
				}

				List(const List<T> &copy): length(0), head(nullptr), tail(nullptr), end_(nullptr)
				{
					*this = copy;
				}

				~List()
				{
					std::cout << "<length> " << this->length << std::endl;
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
					// if (this->end_)
					// 	delete (this->end_);

					this->end_ = List.end_;
					
					insert(begin(), List.begin(), List.end());
					
					return (*this);
				}

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
					
					if (position == begin() || position == end())
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
						if (cur_node == nullptr)
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
					this->tail->next = end_;
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
						if (cur_node == nullptr)
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
					this->tail->next = end_;
				}

				iterator erase (iterator position)
				{
					iterator tmp = iterator(position);
					++tmp;
					return (erase(position, tmp));
				}

				iterator erase (iterator first, iterator last)
				{

					t_node<T> *left_node;
					t_node<T> *right_node;

					if (first.getPtr() == 0 && first.getPtr() != end().getPtr()->prev)
					{
						left_node = nullptr;
						right_node = nullptr;
					}
					else
					{
						left_node = first.getPtr()->prev;
						right_node = first.getPtr()->next;
					}

					iterator ite = first;
					while (ite != last)
					{
						iterator tmp(ite);
						--this->length;
						std::cout << "delete : " << tmp.getPtr()->data << std::endl;
						// if (tmp.getPtr())
						// 	delete (tmp.getPtr());
						++ite;
					}

					if (left_node)
						left_node->next = right_node;
					else
						this->head = right_node;
					
					if (right_node)
						right_node->prev = left_node;
					else
						this->tail = left_node;

					if (this->length == 0)
						this->head = nullptr;

					return (last);
				}

				void	swap (List& x)
				{
					std::swap(this->head, x->head);
					std::swap(this->tail, x->tail);
					std::swap(this->length, x->length);
				}

				void	resize (size_type n, value_type val = value_type())
				{
					if (n < this->length)
					{
						iterator iter = begin();
						for (unsigned int i = 0; i < n; ++i)
							++iter;
						erase(iter, end());
					}
					else if (n > this->length)
						insert(end(), n - this->length, val);
				}

				void 	clear()
				{
					erase(begin(), end());
					this->head = nullptr;
					this->tail = nullptr;
					this->length = 0;
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

					iterator iter = end();
					--iter;
					while (iter != begin())
					{
						iterator tmp = iter;
						--tmp;
						if (*tmp == *iter)
							iter = erase(tmp);
						else
							--iter;
					}
				}

				template <typename BinaryPredicate>
				void	unique (BinaryPredicate binary_pred)
				{
					if (this->length < 2)
						return ;

					iterator iter = end();
					--iter;
					while (iter != begin())
					{
						iterator tmp = iter;
						--tmp;
						if (binary_pred(*tmp, *iter))
							iter = erase(tmp);
						else
							--iter;
					}
				}

				void	merge (List& x)
				{
					if (this == &x)
						return ;
					
					t_node<T> *my_node = this->head;
					t_node<T> *x_node = x.head;
					t_node<T> *x_tmp;

					while (x_node != nullptr)
					{
						if (my_node->data <= x_node->data && my_node != this->tail)
							my_node = my_node->next;
						else if (my_node->data > x_node->data)
						{
							x_tmp = x_node->next;

							if (my_node != this->head)
							{
								my_node->prev->next = x_node;
								x_node->prev = my_node->prev;
							}
							else
								this->head = x_node;
							x_node->next = my_node;
							my_node->prev = x_node;
							
							x_node = x_tmp;
						}
						else
						{
							x_tmp = x_node->next;

							my_node->next = x_node;
							x_node->prev = my_node;
							this->tail = x_node;
							my_node = my_node->next;

							x_node = x_tmp;
						}
					}
					this->length += x.length;
					x.clear(); // x를 아예 없애도 가능한가?
				}

				template <typename Compare>
				void	merge (List& x, Compare comp)
				{
					if (this == &x)
						return ;
					
					t_node<T> *my_node = this->head;
					t_node<T> *x_node = x.head;
					t_node<T> *x_tmp;

					while (x_node != nullptr)
					{
						if (comp(my_node->data, x_node->data) && my_node != this->tail)
							my_node = my_node->next;
						else if (!comp(my_node->data, x_node->data))
						{
							x_tmp = x_node->next;

							if (my_node != this->head)
							{
								my_node->prev->next = x_node;
								x_node->prev = my_node->prev;
							}
							else
								this->head = x_node;
							x_node->next = my_node;
							my_node->prev = x_node;
							
							x_node = x_tmp;
						}
						else
						{
							x_tmp = x_node->next;

							my_node->next = x_node;
							x_node->prev = my_node;
							this->tail = x_node;
							my_node = my_node->next;
							x_node = x_tmp;
						}
					}
					this->length += x.length;
					x.clear(); // x를 아예 없애도 가능한가?
				}

				void	sort()
				{
					iterator iter = begin();
					iterator tmp = iterator(iter);
					while (iter != end())
					{
						tmp = iter;
						++iter;
						if (iter == end())
							break ;
						if (*iter < *tmp)
						{
							std::swap(*tmp, *iter);
							iter = begin();
						}
					}
				}

				template <typename Compare>
				void	sort(Compare comp)
				{
					iterator iter = begin();
					iterator tmp = iterator(iter);
					while (iter != end())
					{
						tmp = iter;
						++iter;
						if (iter == end())
							break ;
						if (comp(*iter, *tmp))
						{
							std::swap(*tmp, *iter);
							iter = begin();
						}
					}
				}

				void	reverse()
				{
					iterator start = begin();
					iterator end = end();
					--end;

					for (unsigned int i = 0; i < this->length / 2; ++i)
					{
						std::swap(*start, *end);
						++start;
						--end;
					}
				}

				template <typename E>
				friend class ListItertor;
	};

	template <class T, class Alloc>
	bool operator== (const List<T, Alloc>& lhs, const List<T, Alloc>& rhs)
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