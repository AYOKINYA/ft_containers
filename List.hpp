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

			void	assign(void);
			T		front(void) const;
			T		back(void) const;
			bool	empty() const;
			void	push_back(const T &elem);
			void	pop_back(void);
			void	push_front(const T &elem);
			void	pop_front(void);

};

#endif