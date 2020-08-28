#ifndef QUEUE_HPP
# define QUEUE_HPP
# include "List.hpp"

namespace ft
{
	template <class T, class Container = List<T> >
	class Queue
	{
		private:
				Container container_;
				
		public:
				typedef	T			value_type;
				typedef	Container	container_type;
				typedef size_t		size_type;

				explicit Queue(const container_type& ctnr = container_type()) : container_(ctnr) {};

				Queue(const Queue& copy) : container_(copy) {};

				Queue& operator=(const Queue& Queue)
				{
					if (this == &Queue)
						return (*this);
					this->container_ = Queue.container_;
					return (*this);
				}
				
				~Queue() {};

				bool	empty() const
				{
					return (container_.empty());
				}

				size_type size() const
				{
					return (container_.size());
				}
				value_type& front()
				{
					return (container_.front());
				}

				const value_type& front() const
				{
					return (container_.front());
				}

				value_type& back()
				{
					return (container_.back());
				}

				const value_type& back() const
				{
					return (container_.back());
				}

				void push (const value_type& val)
				{
					container_.push_back(val);
				}

				void pop()
				{
					container_.pop_front();
				}

				friend bool operator== (const Queue<T , Container>& lhs, const Queue<T , Container>& rhs)
				{
					return (lhs.container_ == rhs.container_);
				}
				friend bool operator!= (const Queue<T , Container>& lhs, const Queue<T , Container>& rhs)
				{
					return (lhs.container_ != rhs.container_);
				}

				friend bool operator< (const Queue<T , Container>& lhs, const Queue<T , Container>& rhs)
				{
					return (lhs.container_ < rhs.container_);
				}

				friend bool operator> (const Queue<T , Container>& lhs, const Queue<T , Container>& rhs)
				{
					return (lhs.container_ > rhs.container_);
				}

	};
	
	template <class T, class Container>
 	bool operator<= (const Queue<T , Container>& lhs, const Queue<T , Container>& rhs)
	{
		return (!(lhs > rhs));
	}

	template <class T, class Container>
 	bool operator>= (const Queue<T , Container>& lhs, const Queue<T , Container>& rhs)
	{
		return (!(lhs < rhs));
	}
};


#endif