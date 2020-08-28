#ifndef AVLTREE_HPP
# define AVLTREE_HPP

# include "Iterator.hpp"
# include <exception>

namespace ft
{
	template <typename Key, typename T>
	struct AVLtreeNode
	{
		pair<Key, T>	data;
		AVLtreeNode*	parent;
		AVLtreeNode*	right;
		AVLtreeNode*	left;
		int				height;
		// 결국에는 Key가 Map에서 const이기 때문에 생성 시 초기화를 해야만 한다!
		// 그래서 멤버 이니셜라이저 리스트 사용
		AVLtreeNode(pair<Key, T> data, AVLtreeNode* parent, AVLtreeNode* right, AVLtreeNode* left, int height)
			: data(data), parent(parent), right(right), left(left), height(height)
		{}
	};

	template <typename Key, typename T>
	class AVLtreeIterator
	{
		protected:
				typedef AVLtreeNode<Key, T> treenode;
				treenode *tree_root_;
				treenode *node_;

		public:
				typedef pair<Key, T>							value_type;
				typedef pair<Key, T>*							pointer;
				typedef pair<Key, T>&							reference;
				typedef std::ptrdiff_t 				difference_type;
				typedef bidirectional_iterator_tag	iterator_category;
				
				AVLtreeIterator() : tree_root_(nullptr), node_(nullptr) {};
		
				AVLtreeIterator(treenode* tree_root_, treenode *n) : tree_root_(tree_root_), node_(n) {};

				AVLtreeIterator(const AVLtreeIterator<Key, T> & copy)
				 : tree_root_(copy.tree_root_), node_(copy.node_)
				{}

				~AVLtreeIterator() {};
				AVLtreeIterator<Key, T>& operator=(const AVLtreeIterator<Key, T> & rhs)
				{
					if (this == &rhs)
						return (*this);
					this->node_ = rhs.node_;
					return (*this);
				}

				AVLtreeIterator<Key, T>& operator++()
				{
					if (!node_)
						return (*this);
					if (node_->right)
					{
						node_ = node_->right;
						while (node_->left)
							node_ = node_->left;
					}
					else
					{
						treenode *tmp;
						do
						{
							tmp = node_;
							node_ = node_->parent;
						}
						while (node_ && tmp == node_->right);
					}

					return (*this);
				}

				AVLtreeIterator<Key, T> operator++(int)
				{
					AVLtreeIterator<Key, T> tmp(*this);
					operator++();
					return (tmp);
				}

				AVLtreeIterator<Key, T>& operator--()
				{
					if (!node_)
					{
						node_ = tree_root_;
						while (node_ && node_->right)
							node_ = node_->right;
					}
					else if (node_->left)
					{
						node_ = node_->left;
						while (node_->right)
							node_ = node_->right;
					}
					else
					{
						treenode *tmp;
						do
						{
							tmp = node_;
							node_ = node_->parent;
						}
						while (node_ && tmp == node_->left);
					}
					return (*this);
				}

				AVLtreeIterator<Key, T> operator--(int)
				{
					AVLtreeIterator<Key, T> tmp(*this);
					operator--();
					return (tmp);
				}

				bool	operator==(const AVLtreeIterator<Key, T> &rhs) const
				{
					return (this->node_ == rhs.node_);
				}

				bool	operator!=(const AVLtreeIterator<Key, T> &rhs) const
				{
					return (this->node_ != rhs.node_);
				}

				pair<Key, T>& operator*(void)
				{
					return (this->node_->data);
				}

				pair<Key, T>& operator*(void) const
				{
					return (this->node_->data);
				}

				pair<Key, T>* operator->(void)
				{
					return (&(this->node_->data));
				}

				treenode	*getPtr(void)
				{
					return (this->node_);
				}
	};

	template <typename Key, typename T>
	class AVLtreeRIterator
	{
		private:
				typedef AVLtreeNode<Key, T>	treenode;
				treenode*					tree_root_;
				treenode*					node_;

		public:
				
				typedef T							value_type;
				typedef T*							pointer;
				typedef T&							reference;
				typedef std::ptrdiff_t 				difference_type;
				typedef bidirectional_iterator_tag	iterator_category;
				
				AVLtreeRIterator() : tree_root_(nullptr), node_(nullptr) {};
		
				AVLtreeRIterator(treenode* tree_root_, treenode *n) : tree_root_(tree_root_), node_(n) {};

				AVLtreeRIterator(const AVLtreeRIterator<Key, T> & copy)
				 : tree_root_(copy.tree_root_), node_(copy.node_)
				{}

				~AVLtreeRIterator() {};
				AVLtreeRIterator<Key, T>& operator=(const AVLtreeRIterator<Key, T> & rhs)
				{
					if (this == &rhs)
						return (*this);
					this->node_ = rhs.node_;
					return (*this);
				}

				AVLtreeRIterator<Key, T>& operator--()
				{
					if (!node_)
						return (*this);
					if (node_->right)
					{
						node_ = node_->right;
						while (node_->left)
							node_ = node_->left;
					}
					else
					{
						treenode *tmp;
						do
						{
							tmp = node_;
							node_ = node_->parent;
						}
						while (node_ && tmp == node_->right);
					}

					return (*this);
				}

				AVLtreeRIterator<Key, T> operator--(int)
				{
					AVLtreeRIterator<Key, T> tmp(*this);
					operator--();
					return (tmp);
				}

				AVLtreeRIterator<Key, T>& operator++()
				{
					if (!node_)
					{
						node_ = tree_root_;
						while (node_ && node_->right)
							node_ = node_->right;
					}
					else if (node_->left)
					{
						node_ = node_->left;
						while (node_->right)
							node_ = node_->right;
					}
					else
					{	
						treenode *tmp;
						
						do
						{
							tmp = node_;
							node_ = node_->parent;
						}
						while (node_ && tmp == node_->left);
					}
					return (*this);
				}

				AVLtreeRIterator<Key, T> operator++(int)
				{
					AVLtreeRIterator<Key, T> tmp(*this);
					operator++();
					return (tmp);
				}

				bool	operator==(const AVLtreeRIterator<Key, T> &rhs) const
				{
					return (this->node_ == rhs.node_);
				}

				bool	operator!=(const AVLtreeRIterator<Key, T> &rhs) const
				{
					return (this->node_ != rhs.node_);
				}

				pair<Key, T>& operator*(void)
				{
					return (this->node_->data);
				}

				pair<Key, T>* operator->(void)
				{
					return (&(this->node_->data));
				}

				treenode	*getPtr(void)
				{
					return (this->node_);
				}
	};

	template <typename Key, typename T>
 	bool operator== (const AVLtreeRIterator<Key, T>& lhs, const AVLtreeRIterator<Key, T>& rhs)
	{
		return (lhs.getPtr() == rhs.getPtr());
	}
	template <typename Key, typename T>
	bool operator!= (const AVLtreeRIterator<Key, T>& lhs, const AVLtreeRIterator<Key, T>& rhs)
	{
		return (lhs.getPtr() != rhs.getPtr());
	}
	template <typename Key, typename T>
	bool operator<  (const AVLtreeRIterator<Key, T>& lhs, const AVLtreeRIterator<Key, T>& rhs)
	{
		return (lhs.getPtr()->data.first > rhs.getPtr()->data.first);
	}
	template <typename Key, typename T>
	bool operator<= (const AVLtreeRIterator<Key, T>& lhs, const AVLtreeRIterator<Key, T>& rhs)
	{
		return (lhs.getPtr()->data.first >= rhs.getPtr()->data.first);
	}
	template <typename Key, typename T>
	bool operator>  (const AVLtreeRIterator<Key, T>& lhs, const AVLtreeRIterator<Key, T>& rhs)
	{
		return (lhs.getPtr()->data.first < rhs.getPtr()->data.first);
	}
	template <typename Key, typename T>
	bool operator>= (const AVLtreeRIterator<Key, T>& lhs, const AVLtreeRIterator<Key, T>& rhs)
	{
		return (lhs.getPtr()->data.first <= rhs.getPtr()->data.first);
	}
	template <typename Key, typename T>
	AVLtreeRIterator<Key, T> operator+(typename AVLtreeRIterator<Key, T>::difference_type n,
											const AVLtreeRIterator<Key, T>& rev_it)
	{
		AVLtreeRIterator<Key, T> res(rev_it.getPtr() - n);
		return (res);
	}

	template <typename Key, typename T>
	AVLtreeRIterator<Key, T> operator-(typename AVLtreeRIterator<Key, T>::difference_type n,
											const AVLtreeRIterator<Key, T>& rev_it)
	{
		AVLtreeRIterator<Key, T> res(rev_it.getPtr() + n);
		return (res);
	}

};

#endif