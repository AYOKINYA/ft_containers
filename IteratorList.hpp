#ifndef ITERATORLIST_HPP
# define ITERATORLIST_HPP

# include "Iterator.hpp"
namespace ft
{
	template <typedef T>
	struct t_list
	{
		T*		data;
		t_list	*prev;
		t_list	*next;

	}

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
					return (*(this->ptr->data));
				}

				T* operator->(void)
				{
					return (this->ptr->data);
				}

				t_list<T>	*getPtr(void)
				{
					return (this->ptr);
				}
	};



};

#endif