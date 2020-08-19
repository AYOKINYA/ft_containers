#include "List.hpp"
#include <limits>

typedef <typename T>
List<T>::List() : size(0), head(nullptr), tail(nullptr)
{}

typedef <typename T>
List<T>::~List()
{
	//lst clear하는 함수로 대체

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
	this->size = list.size;
	this->head = list.head;
	this->tail = list.tail;
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
	return (iterator(this->tail));
}

typedef <typename T>
const_iterator List<T>::end(void)
{
	return (const_iterator(this->tail));
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

// template <typename T, typename InputIt>
// void List<T>::assign(InputIt first, InputIt last)
// {

// }

// typedef <typename T>
// void List<T>::assign(size_type n, const value_type& val)
// {

// }

iterator List<T>::insert (iterator position, const value_type& val)
{
	insert(position, 1, val);

	return (iterator(position.ptr->prev));
}

void List<T>::insert (iterator position, size_type n, const value_type& val)
{
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

template <class InputIterator>
void List<T>::insert (iterator position, InputIterator first, InputIterator last)
{
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
void	List<T>::push_back(const value_type& elem)
{
	t_list *new_node = new t_node();
	new_node->data = elem;
	new_node->prev = nullptr;
	new_node->next = nullptr;

	t_list *node = this->tail;
	if (node == nullptr)
		this->head = new_node;
	else
	{
		node->next = new_node;
		new_node->prev = node;
	}
	this->tail = new_node;
	++this->size;
}

typedef <typename T>
void	List<T>::pop_back(void)
{
	if (this->size == 0)
		return ;

	t_list *node = this->tail;
	if (this->size == 1)
	{
		this->tail = nullptr;
		this->head = nullptr;
	}
	else
	{
		node->prev->next = nullptr;
		this->tail = node->prev;
	}
	delete node;
	--this->size;
}

typedef <typename T>
void	List<T>::push_front(const value_type & elem)
{
	if (this == 0)
		return ;

	t_list *new_node = new t_node();
	new_node->data = elem;
	new_node->prev = nullptr;
	new_node->next = nullptr;

	t_list *node = this->head;
	if (node == nullptr)
		this->tail = new_node;
	else
	{
		node->prev = new_node;
		new_node->next = node;
	}
	this->head = new_node;
	++this->size;
}

typedef <typename T>
void	List<T>::pop_front(void)
{
	if (this->size == 0)
		return ;

	t_list *node = this->head;
	if (this->size == 1)
	{
		this->tail = nullptr;
		this->head = nullptr;
	}
	else
	{
		node->next->prev = nullptr;
		this->head = node->next;
	}
	delete node;
	--this->size;
}