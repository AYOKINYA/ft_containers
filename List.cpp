#include "List.hpp"

typedef <typename T>
List<T>::List() : lst(nullptr)
{
	this->lst = new t_list();
	if (this->lst == 0)
		exit(12);
	this->lst->size = 0;
	this->lst->head = nullptr;
	this->lst->tail = nullptr;
}

typedef <typename T>
List<T>::~List()
{
	//lst clear하는 함수로 대체
	if (this->lst)
		delete this->lst;
}

typedef <typename T>
List<T>::List(const List & copy)
{
	*this = copy;
}

typedef <typename T>
List<T>& operator=(const List &list)
{
	if (this == &list)
		return (*this);

	return (*this);
}

typedef <typename T>
T	List<T>::front(void) const
{
	if (this->lst == nullptr)
		return (0);
	if (this->lst->head == nullptr)
		return (0);
	return (this->lst->head->data);
}

typedef <typename T>
T	List<T>::back(void) const
{
	if (this->lst == nullptr)
		return (0);
	if (this->lst->tail == nullptr)
		return (0);
	return (this->lst->tail->data);
}

typedef <typename T>
void	List<T>::push_back(const T & elem)
{
	if (this->lst == 0)
		return ;

	t_list *new_node = new t_node();
	new_node->data = elem;
	new_node->prev = nullptr;
	new_node->next = nullptr;

	t_list *node = this->lst->tail;
	if (node == nullptr)
		this->lst->head = new_node;
	else
	{
		node->next = new_node;
		new_node->prev = node;
	}
	this->lst->tail = new_node;
	++this->size;
}

typedef <typename T>
void	List<T>::pop_back(void)
{
	if (this->lst == nullptr)
		return ;
	if (this->lst->size == 0)
		return ;

	t_list *node = this->lst->tail;
	if (this->lst->size == 1)
	{
		this->lst->tail = nullptr;
		this->lst->head = nullptr;
	}
	else
	{
		node->prev->next = nullptr;
		this->lst->tail = node->prev;
	}
	delete node;
	--this->size;
}

typedef <typename T>
void	List<T>::push_front(const T & elem)
{
	if (this->lst == 0)
		return ;

	t_list *new_node = new t_node();
	new_node->data = elem;
	new_node->prev = nullptr;
	new_node->next = nullptr;

	t_list *node = this->lst->head;
	if (node == nullptr)
		this->lst->tail = new_node;
	else
	{
		node->prev = new_node;
		new_node->next = node;
	}
	this->lst->head = new_node;
	++this->size;
}

typedef <typename T>
void	List<T>::pop_front(void)
{
	if (this->lst == nullptr)
		return ;
	if (this->lst->size == 0)
		return ;

	t_list *node = this->lst->head;
	if (this->lst->size == 1)
	{
		this->lst->tail = nullptr;
		this->lst->head = nullptr;
	}
	else
	{
		node->next->prev = nullptr;
		this->lst->head = node->next;
	}
	delete node;
	--this->size;
}