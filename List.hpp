#ifndef LIST_HPP
# define LIST_HPP
# include <memory>
# include <cstddef>

template <typename T, typename Allocator = std::allocator<T>>
class List
{
	private:
			typedef struct		s_node
			{
				T				*data;
				struct s_node	*prev;
				struct s_node	*next;
			}					t_node;

			typedef struct		s_list
			{
				unsigned int	size;
				t_node			*head;
				t_node			*tail;
			}					t_list;

			t_list				*lst;
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
			void	push_back(const value_type&elem);
			void	pop_back(void);
			void	push_front(const value_typ&elem);
			void	pop_front(void);

};

#endif