#include "List.hpp"
#include <limits>

typedef <typename T>
explicit List<T>::List(const allocator_type& alloc = allocator_type())
	: size(0), head(nullptr), tail(nullptr)
{
	this->end_ = new t_node();
	this->end_->next = nullptr;
	this->end_->prev = this->tail;

}

typedef <typename T>
explicit List<T>::List(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	: size(0), head(nullptr), tail(nullptr)
{

	this->end_ = new t_node();
	this->end_->next = nullptr;
	this->end_->prev = this->tail;
	
	insert(begin(), n, val);
}

template <typename T, class InputIterator>
List<T>::List(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
	: size(0), head(nullptr), tail(nullptr)
{
	this->end_ = new t_node();
	this->end_->next = nullptr;
	this->end_->prev = this->tail;
	
	insert(begin(), first, last);
}

typedef <typename T>
List<T>::~List()
{
	clear();

	delete (this->end_);
}

typedef <typename T>
List<T>::List(const List & copy) : size(0), head(nullptr), tail(nullptr)
{
	*this = copy;
}

typedef <typename T>
List<T>& operator=(const List &list)
{
	if (this == &list)
		return (*this);
	
	clear();

	delete (this->end_);

	this.end_ = list.end_;

	insert(begin(), list.begin(), list.end());

	return (*this);
}

typedef <typename T>
iterator List<T>::begin(void)
{
	return (iterator(this->head));
}

typedef <typename T>
const_iterator List<T>::begin(void)
{
	return (const_iterator(this->head));
}

typedef <typename T>
iterator List<T>::end(void)
{
	return (iterator(this->end_));
}

typedef <typename T>
const_iterator List<T>::end(void)
{
	return (const_iterator(this->end_));
}

typedef <typename T>
reverse_iterator List<T>::rbegin(void)
{
	return (reverse_iterator(end()));
}

typedef <typename T>
const_reverse_iterator List<T>::rbegin(void)
{
	return (const_reverse_iterator(end()));
}

typedef <typename T>
reverse_iterator List<T>::rend(void)
{
	return (reverse_iterator(begin()));
}

typedef <typename T>
const_reverse_iterator List<T>::rend(void)
{
	return (const_reverse_iterator(begin()));
}

typedef <typename T>
bool List<T>::empty(void)
{
	return (this->size == 0)
}

typedef <typename T>
size_type List<T>::size(void)
{
	return (this->size);
}


typedef <typename T>
size_type List<T>::size(void)
{
	return (std::numeric_limits<size_type>::max() / sizeof(this->head));
}

typedef <typename T>
reference	List<T>::front(void)
{
	if (this->head == nullptr)
		return (0);
	return (this->head->data);
}

typedef <typename T>
const_reference	List<T>::front(void) const
{
	if (this->head == nullptr)
		return (0);
	return (this->head->data);
}

typedef <typename T>
reference	List<T>::back(void)
{
	if (this->tail == nullptr)
		return (0);
	return (this->tail->data);
}

typedef <typename T>
const_reference	List<T>::back(void) const
{
	if (this->tail == nullptr)
		return (0);
	return (this->tail->data);
}

template <typename T, typename InputIt>
void List<T>::assign(InputIt first, InputIt last)
{
	clear();
	insert(begin(), first, last);
}

typedef <typename T>
void List<T>::assign(size_type n, const value_type& val)
{
	clear();
	insert(begin(), n, val);
}

typedef <typename T>
iterator List<T>::insert (iterator position, const value_type& val)
{
	insert(position, 1, val);

	if (position == begin())
		return (iterator(this->head));
	else
		return (iterator(position.ptr->prev->next));
}

typedef <typename T>
void List<T>::insert (iterator position, size_type n, const value_type& val)
{
	if (this->size == 0)
		t_node *cur_node = nullptr;
	else
		t_node *cur_node = position.ptr;
	t_node *left_node = position.ptr->prev;

	for (unsigned int i = 0; i < n; i++)
	{
		t_node *new_node = new t_node();
		
		new_node->prev = left_node;
		new_node->next = nullptr;
		new_node->data = val;

		if (left_node)
			left_node->next = new_node;
		else
			this->head = new_node;
		++this->size;
		left_node = new_node;
	}

	if (cur_node)
	{
		cur_node->prev = left_node;
		left_node->next = cur_node;
	}
	else
		this->tail = left_node;

}

template <typename T, class InputIterator>
void List<T>::insert (iterator position, InputIterator first, InputIterator last)
{
	if (this->size == 0)
		t_node *cur_node = 0;
	else
		t_node *cur_node = position.ptr;
	t_node *left_node = position.ptr->prev;

	for (InputIterator ite = first; ite != last; ++ite)
	{
		t_node *new_node = new t_node();
		
		new_node->prev = left_node;
		new_node->next = nullptr;
		new_node->data = *ite;

		if (left_node)
			left_node->next = new_node;
		else
			this->head = new_node;
		++this->size;
		left_node = new_node;
	}

	if (cur_node)
	{
		cur_node->prev = left_node;
		left_node->next = cur_node;
	}
	else
		this->tail = left_node;
}

typedef <typename T>
iterator List<T>::erase (iterator first, iterator last)
{
	if (first.ptr == 0)
	{
		t_node *left_node = nullptr;
		t_node *right_node = nullptr;
	}
	else
	{
		t_node *left_node = first.ptr->prev;
		t_node *right_node = first.ptr->next;
	}

	iterator ite = first;
	while (ite != last)
	{
		iterator tmp(ite);
		--this->size;
		++ite;
		delete (*tmp);
	}

	if (left_node)
		left_node->next = right_node;
	else
		this->head = right_node;
	
	if (right_node)
		right_node->prev = left_node;
	else
		this->tail = left_node;

	last.ptr->prev = first.ptr;
	//first.ptr은 위에서 계속 조작해서 따로 해줄 필요 없다.
	return (iterator(last));
}

typedef <typename T>
iterator List<T>::erase (iterator position)
{
	iterator tmp = iterator(position);
	++tmp;
	return (erase(position, tmp));
}

typedef <typename T>
void	List<T>::swap (List& x)
{
	std::swap(this->head, x->head);
	std::swap(this->tail, x->tail);
	std::swap(this->size, x->size);
}

typedef <typename T>
void	List<T>::resize (size_type n, value_type val = value_type())
{
	if (n < this->size)
	{
		iterator iter = begin();
		for (unsigned int i = 0; i < n; ++i)
			++iter;
		erase(iter, end());
	}
	else if (n > this->size)
		insert(end(), n - this->size, val);
}

typedef <typename T>
void 	List<T>::clear()
{
	erase(begin(), end());
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

typedef <typename T>
void	List<T>::push_front(const value_type & elem)
{
	insert(begin(), val);
}

typedef <typename T>
void	List<T>::pop_front(void)
{
	erase(begin());
}

typedef <typename T>
void	List<T>::push_back(const value_type& val)
{
	insert(end(), val);
}

typedef <typename T>
void	List<T>::pop_back(void)
{
	iterator iter = end();
	--iter;
	erase(iter);
}

typedef <typename T>
void	List<T>::splice (iterator position, list& x)
{
	insert(position, x.begin(), x.end());
	x.clear();
}

typedef <typename T>
void	List<T>::splice (iterator position, list& x, iterator i)
{
	insert(position, *i);
	x.erase(i);
}

typedef <typename T>
void	List<T>::splice (iterator position, list& x, iterator first, iterator last)
{
	insert(position, first, last);
	x.erase(first, last);
}

typedef <typename T>
void	List<T>::remove (const value_type& val)
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

template <typename T, typename Predicate>
void	List<T>::remove_if (Predicate pred)
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

template <typename T>
void	List<T>::unique()
{
	if (this->size < 2)
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

template <typename T, typename BinaryPredicate>
void	List<T>::unique (BinaryPredicate binary_pred)
{
	if (this->size < 2)
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

template <typename T>
void	List<T>::merge (list& x)
{
	if (this == &x)
		return ;
	
	t_node *my_node = this->head;
	t_node *x_node = x.head;
	t_node *x_tmp;

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
	this->size += x.size;
	x.clear(); // x를 아예 없애도 가능한가?
}

template <typename T, typename Compare>
void	List<T>::merge (list& x, Compare comp)
{
	if (this == &x)
		return ;
	
	t_node *my_node = this->head;
	t_node *x_node = x.head;
	t_node *x_tmp;

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
	this->size += x.size;
	x.clear(); // x를 아예 없애도 가능한가?
}

template <typename T>
void	List<T>::sort()
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

template <typename T, typename Compare>
void	List<T>::sort(Compare comp)
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

template <typename T>
void	List<T>::reverse()
{
	iterator start = begin();
	iterator end = end();
	--end;

	for (unsigned int i = 0; i < this->size / 2; ++i)
	{
		std::swap(*start, *end);
		++start;
		--end;
	}
}