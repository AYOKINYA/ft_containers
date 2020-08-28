#ifndef Stack_HPP
# define Stack_HPP
# include "List.hpp"

namespace ft
{
	template <class T, class Container = List<T> >
	class Stack
	{
		private:
				Container container_;
				
				Stack(const Stack& copy) : container_(copy) {};

				Stack& operator=(const Stack& stack)
				{
					if (this == &stack)
						return (*this);
					this->container_ = stack.container_;
					return (*this);
				}
		public:
				typedef	T			value_type;
				typedef	Container	container_type;
				typedef size_t		size_type;

				explicit Stack(const container_type& ctnr = container_type())
				{
					this->container_ = ctnr;
				};

				~Stack() {};

				bool	empty() const
				{
					return (container_.empty());
				}

				size_type size() const
				{
					return (container_.size());
				}
				value_type& top()
				{
					return (container_.back());
				}

				const value_type& top() const
				{
					return (container_.back());
				}

				void push (const value_type& val)
				{
					container_.push_back(val);
				}

				void pop()
				{
					container_.pop_back();
				}

				friend bool operator== (const Stack<T , Container>& lhs, const Stack<T , Container>& rhs)
				{
					return (lhs.container_ == rhs.container_);
				}
				friend bool operator!= (const Stack<T , Container>& lhs, const Stack<T , Container>& rhs)
				{
					return (lhs.container_ != rhs.container_);
				}

				friend bool operator< (const Stack<T , Container>& lhs, const Stack<T , Container>& rhs)
				{
					return (lhs.container_ < rhs.container_);
				}

				friend bool operator> (const Stack<T , Container>& lhs, const Stack<T , Container>& rhs)
				{
					return (lhs.container_ > rhs.container_);
				}

	};
	
	template <class T, class Container>
 	bool operator<= (const Stack<T , Container>& lhs, const Stack<T , Container>& rhs)
	{
		return (!(lhs > rhs));
	}

	template <class T, class Container>
 	bool operator>= (const Stack<T , Container>& lhs, const Stack<T , Container>& rhs)
	{
		return (!(lhs < rhs));
	}
};


#endif