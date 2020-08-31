#ifndef Multimap_HPP
# define Multimap_HPP
# include "Iterator.hpp"
# include <memory>
# include <limits>

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
		// 결국에는 Key가 AVLtree에서 const이기 때문에 생성 시 초기화를 해야만 한다!
		// 그래서 멤버 이니셜라이저 리스트 사용
		AVLtreeNode(pair<Key, T> data, AVLtreeNode* parent, AVLtreeNode* right, AVLtreeNode* left, int height)
			: data(data), parent(parent), right(right), left(left), height(height)
		{}
	};
	template <typename Key, typename T, typename k_cmp>
	class AVLtree;

	template <typename Key, typename T, typename k_cmp>
	class AVLtreeIterator
	{
		private:
				typedef AVLtree<Key, T, k_cmp> 		tree;
				typedef typename tree::node			treenode;
			
				treenode 							*tree_root_;
				treenode 							*node_;

		public:
				typedef pair<Key, T>				value_type;
				typedef pair<Key, T>*				pointer;
				typedef pair<Key, T>&				reference;
				typedef std::ptrdiff_t 				difference_type;
				typedef bidirectional_iterator_tag	iterator_category;
				
				AVLtreeIterator() : tree_root_(nullptr), node_(nullptr) 
				{};
		
				AVLtreeIterator(treenode* tree_root_, treenode *n) : tree_root_(tree_root_), node_(n)
				{};

				AVLtreeIterator(const AVLtreeIterator<Key, T, k_cmp> & copy)
				 : tree_root_(copy.tree_root_), node_(copy.node_)
				{};

				~AVLtreeIterator() {};
				AVLtreeIterator<Key, T, k_cmp>& operator=(const AVLtreeIterator<Key, T, k_cmp> & rhs)
				{
					if (this == &rhs)
						return (*this);
					this->node_ = rhs.node_;
					return (*this);
				}

				AVLtreeIterator<Key, T, k_cmp>& operator++()
				{
					if (!node_)
					{
						node_ = tree_root_;
						while (node_ && node_->left)
							node_ = node_->left;
					}
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

				AVLtreeIterator<Key, T, k_cmp> operator++(int)
				{
					AVLtreeIterator<Key, T, k_cmp> tmp(*this);
					operator++();
					return (tmp);
				}

				AVLtreeIterator<Key, T, k_cmp>& operator--()
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

				AVLtreeIterator<Key, T, k_cmp> operator--(int)
				{
					AVLtreeIterator<Key, T, k_cmp> tmp(*this);
					operator--();
					return (tmp);
				}

				bool	operator==(const AVLtreeIterator<Key, T, k_cmp> &rhs) const
				{
					return (this->node_ == rhs.node_);
				}

				bool	operator!=(const AVLtreeIterator<Key, T, k_cmp> &rhs) const
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

	template <typename Key, typename T, typename k_cmp>
	class AVLtree
	{
		public:
				typedef pair<Key, T>								value_type;
				typedef AVLtreeIterator<Key, T, k_cmp> 				iterator;
				typedef AVLtreeIterator<Key, T, k_cmp>				const_iterator;
				typedef ReverseIterator<iterator>				reverse_iterator;
				typedef ReverseIterator<const_iterator>				const_reverse_iterator;
				typedef size_t										size_type;
				typedef std::ptrdiff_t								difference_type;
		
				typedef AVLtreeNode<Key, T>							node;
				typedef	Key											key_type;
				typedef	T											mapped_type;

				typedef std::allocator<pair<const Key,T> >			allocator_type;

		private:

				k_cmp			k_cmp_;
				node*			root_;
				size_type		len_;
				allocator_type  alloc_;
				
				int getMax(int a, int b)
				{
					return (a > b ? a : b);
				}

				int balance_factor(node *n)
				{
					if (!n)
						return (0);
					return (n->left ? n->left->height : 0) - (n->right ? n->right->height : 0);
				}

				//모든 노드는 회전을 수행한 이후에 높이 다시 계산한다.
				void setHeight(node *n)
				{
					int l_height = n->left ? n->left->height : 0;
					int r_height = n->right ? n->right->height : 0;
					
					n->height = getMax(l_height, r_height) + 1;
				}

				node*	rotateLL(node *n) // right rotate
				{
					if (!n->parent)
						this->root_ = n->left;
					node *tmp = n->left;
					node *tmp_parent = n->parent;
					n->left  = tmp->right;
					tmp->right = n;
					tmp->parent = tmp_parent;
					n->parent = tmp;
					if (n->left)
						n->left->parent = n;
					setHeight(n);
					setHeight(tmp);
					return (tmp);
				}

				node*	rotateRR(node *n) //left rotate
				{
					if (!n->parent)
						this->root_ = n->right;
					node *tmp = n->right;
					node *tmp_parent = n->parent;
					n->right  = tmp->left;
					tmp->left = n;
					tmp->parent = tmp_parent;
					n->parent = tmp;
					if (n->right)
						n->right->parent = n;

					setHeight(n);
					setHeight(tmp);
					return (tmp);
				}

				node*	rotateLR(node *n) //left rotate & right rotate
				{
					node *tmp = n->left;
					n->left = rotateRR(tmp);
					return (rotateLL(n));
				}

				node*	rotateRL(node *n) //right rotate & left rotate
				{
					node *tmp = n->right;				
					n->right = rotateLL(tmp);
					return (rotateRR(n));
				}

				node*	insert_node(node *n, const value_type &data) // with balancing nodes
				{
					if (!n)
					{
						n = new node(data, nullptr, nullptr, nullptr, 1);

						if (!this->root_)
							this->root_ = n;
						return (n);
					}
					else if (k_cmp_(data.first, n->data.first))//(data.first < n->data.first)
					{
						n->left = insert_node(n->left, data);
						n->left->parent = n;
					}
					else if (k_cmp_(n->data.first, data.first))
					{
						n->right = insert_node(n->right, data);
						n->right->parent = n;
					}
					else
					{
						n->right = insert_node(n->right, data);
						n->right->parent = n;
					}
					
					setHeight(n);
					
					//balancing node
					int bf = balance_factor(n);

					if (bf > 1 && data.first < n->left->data.first)
						return rotateLL(n);
					if (bf < -1 && data.first > n->right->data.first)
						return rotateRR(n);
					if (bf > 1 && data.first > n->left->data.first)
						return rotateLR(n);
					if (bf < -1 && data.first < n->right->data.first)
						return rotateRL(n);

					return (n);
				}

				node *minValueNode(node* n)  
				{  
					node* cur = n;  
				
					/* loop down to find the leftmost leaf */
					while (cur && cur->left != NULL)  
						cur = cur->left;  
				
					return cur;  
				}  

				node*	delete_node(node **n, const value_type &data)
				{
					if (n == nullptr)
						return (nullptr);
					if (*n == nullptr)	
						return (*n);
					if (data.first < (*n)->data.first)
						(*n)->left = delete_node(&((*n)->left), data);
					else if (data.first > (*n)->data.first)
						(*n)->right = delete_node(&((*n)->right), data);
					else
					{
						if ((*n)->left == nullptr || (*n)->right == nullptr)
						{
							node *tmp = nullptr;
							tmp = (*n)->left ? (*n)->left : (*n)->right;
							
							// no child case : n->left == nullptr && n->right == nullptr
							if (tmp == NULL)
							{
								//std::cout << n->data.first  << std::endl;
								tmp = (*n);
								(*n) = nullptr;
								delete (tmp);
							}
							else // one child case
							{
								node *temp = (*n);
								(*n) = tmp;
								(*n)->parent = temp->parent;
								delete (temp);
							}
						}
						else
						{	// node with two children;
							//n->data = tmp->data; 한 줄이면 될 것을.... const Key라서 이 고생을 했다.
							node *tmp = minValueNode((*n)->right);
							node *n_new = new node((*n)->data, nullptr, tmp->right, tmp->left, tmp->height);
							if (n_new->right)
								n_new->right->parent = n_new;
							if (n_new->left)
								n_new->left->parent = n_new;
							
							tmp->height = (*n)->height;
							tmp->left = (*n)->left;
							tmp->right = n_new;
							if (tmp->left)
								tmp->left->parent = tmp;
							if (tmp->right)
								tmp->right->parent = tmp;
							n_new->parent = tmp;
							tmp->parent = (*n)->parent;
							if (tmp->parent && tmp->parent->left && tmp->parent->left->data.first == tmp->data.first)
								tmp->parent->left = tmp;
							if (tmp->parent && tmp->parent->right && tmp->parent->right->data.first == tmp->data.first)
								tmp->parent->right = tmp;

							node *temp = (*n);
							(*n) = tmp;
							delete (temp);
							
							(*n)->right = delete_node(&((*n)->right), n_new->data);
						}
						if ((*n) == nullptr)
							return (*n);

						setHeight((*n));
						int bf = balance_factor((*n));
						if (bf > 1 && balance_factor((*n)->left) >= 0)
							return rotateLL((*n));
						if (bf < -1 && balance_factor((*n)->right) < 0)
							return rotateRR((*n));
						if (bf > 1 && balance_factor((*n)->left) < 0)
							return rotateLR((*n));
						if (bf < -1 && balance_factor((*n)->right) > 0)
							return rotateRL((*n));
					}
					return (*n);
				}

		public:
				
				/*
				** constructors
				*/
				explicit AVLtree(const k_cmp& comp = k_cmp(), const allocator_type& alloc = allocator_type())
					: k_cmp_(comp), root_(nullptr), len_(0), alloc_(alloc)
				{}
				
				template <class InputIterator>
				AVLtree(InputIterator first, InputIterator last, const k_cmp& comp = k_cmp(), const allocator_type& alloc = allocator_type())
					: k_cmp_(comp), root_(nullptr), len_(0), alloc_(alloc)
				{
					insert(first, last);
				}

				AVLtree(const AVLtree &x) : k_cmp_(k_cmp()), root_(nullptr), len_(0), alloc_(allocator_type())
				{
					*this = x;
				}

				~AVLtree()
				{
					clear();
				}

				AVLtree& operator=(const AVLtree &AVLtree)
				{
					this->clear();

					insert(AVLtree.begin(), AVLtree.end());

					return (*this);
				}
				/*
				** iterators
				*/
				iterator begin()
				{
					node *ret = this->root_;
					while (ret && ret->left)
						ret = ret->left;
					return (iterator(this->root_, ret));
				}

				const_iterator begin() const
				{
					node *ret = this->root_;
					while (ret && ret->left)
						ret = ret->left;
					return (const_iterator(this->root_, ret));
				}

				iterator end()
				{
					return (iterator(this->root_, NULL));
				}

				const_iterator end() const
				{
					return (const_iterator(this->root_, NULL));
				}

				reverse_iterator rbegin()
				{					
					return (reverse_iterator(end()));
				}

				const_reverse_iterator rbegin() const
				{
					return (const_reverse_iterator(end()));

				}

				reverse_iterator rend()
				{
					return (reverse_iterator(begin()));

				}

				const_reverse_iterator rend() const
				{
					return (const_reverse_iterator(begin()));
				}
				/*
				** capacity
				*/
				bool					empty(void) const
				{
					return (!this->len_);
				}

				size_type				size(void) const
				{
					return (this->len_);
				}

				size_type				max_size(void) const
				{
					return (std::numeric_limits<size_type>::max()/sizeof(this->root_));
				}
				/*
				** Element access
				*/
				
				iterator insert(const value_type& val)
				{
					node *n = insert_node(root_, val);
					n = find(val.first).getPtr();
					++this->len_;

					return (iterator(this->root_, n));
				}

				iterator insert(iterator position, const value_type& val)
				{
					node *hint = position.getPtr();
					node *n = insert_node(hint, val);
					n = find(val.first).getPtr();
					++this->len_;
					return (iterator(this->root_, n));
				}
					
				template <class InputIterator>
				void insert(InputIterator first, InputIterator last)
				{
					InputIterator iter = first;
					while (iter != last)
					{
						insert_node(root_ , *iter);
						++this->len_;
						++iter;
					}
				}

    			void erase (iterator position)
				{
					node *n = position.getPtr();
					if (root_)
						delete_node(&root_, n->data);
					--this->len_;
				}

				size_type erase (const key_type& k)
				{
					iterator iter = begin();
					iterator last = end();
					size_type ret = 0;
					
					iterator next;
					while (iter != last)
					{
						next = iter;
						if (next.getPtr() != nullptr)
							++next;
						if (k == iter->first)
						{
							if (root_)
								delete_node(&root_, k);
							--this->len_;
							++ret;
						}
						iter = next;
					}
					return (ret);
				}

				void erase (iterator first, iterator last)
				{
					iterator next;

					while (first != last)
					{
						next = first;
						if (next.getPtr() != nullptr)
							++next;
						if (root_)
							delete_node(&root_, *first);
						--this->len_;
						first = next;
					}
				}

				void swap (AVLtree& x)
				{
					std::swap(alloc_, x.alloc_);
					std::swap(k_cmp_, x.k_cmp_);
					std::swap(root_, x.root_);
					std::swap(len_, x.len_);
				}
				void clear()
				{
					erase(begin(), end());
					this->len_ = 0;
				}
				/*
				** observers
				*/
				k_cmp			 key_comp() const
				{
					return (this->k_cmp_);
				}

				/*
				** operations
				*/
				iterator find (const key_type& k)
				{
					node *n;

					n = this->root_;
					while (n)
					{
						if (k == n->data.first)
							return (iterator(this->root_, n));
						if (k_cmp_(k, n->data.first))
							n = n->left;
						else
							n = n->right;
					}
					
					return (this->end());
				}
				const_iterator find (const key_type& k) const
				{
					node *n;

					n = this->root_;
					while (n)
					{
						if (k == n->data.first)
							return (const_iterator(this->root_, n));
						if (k_cmp_(k, n->data.first))
							n = n->left;
						else
							n = n->right;
					}
					return (this->end());
				}
				size_type count (const key_type& k) const
				{					
					iterator iter = begin();
					iterator last = end();
					size_type ret = 0;
					
					while (iter != last)
					{
						if (k == iter->first)
							++ret;
						++iter;
					}
					return (ret);
				}

				iterator	lower_bound(const key_type& k)
				{
					iterator start = begin();
					iterator last = end();
					k_cmp k_comp = k_cmp();

					while (start != last)
					{
						if (k_comp((*start).first, k) <= 0)
							return (iterator(this->root_, start.getPtr()));
						++start;
					}
					return (this->end());
				}

				const_iterator	lower_bound(const key_type& k) const
				{
					iterator start = begin();
					iterator last = end();
					k_cmp k_comp = k_cmp();

					while (start != last)
					{
						if (k_comp((*start).first, k) <= 0)
							return (const_iterator(this->root_, start.getPtr()));
						++start;
					}
					return (this->end());
				}

				iterator	upper_bound(const key_type& k)
				{
					iterator start = begin();
					iterator last = end();
					k_cmp k_comp = k_cmp();

					while (start != last)
					{
						if ((*start).first == k)
							return (iterator(this->root_, (++start).getPtr()));
						if (k_comp((*start).first, k) <= 0)
							return (iterator(this->root_, start.getPtr()));
						++start;
					}
					return (this->end());
				}

				const_iterator	upper_bound(const key_type& k) const
				{
					iterator start = begin();
					iterator last = end();
					k_cmp k_comp = k_cmp();

					while (start != last)
					{
						if ((*start).first == k)
							return (const_iterator(this->root_, (++start).getPtr()));
						if (k_comp((*start).first, k) <= 0)
							return (const_iterator(this->root_, start.getPtr()));
						++start;
					}
					return (this->end());
				}

				pair<iterator, iterator> equal_range(const key_type& k)
				{
					return ft::make_pair(lower_bound(k), upper_bound(k));
				}

				pair<const_iterator, const_iterator> equal_range(const key_type& k) const
				{
					return ft::make_pair(lower_bound(k), upper_bound(k));
				}

	};

	template <typename Key, typename T, class Compare = std::less<Key>, typename Alloc = std::allocator<pair<const Key,T> > >
	class Multimap
	{
		public:
				
				typedef	Key													key_type;
				typedef	T													mapped_type;
				typedef pair<const key_type, mapped_type>					value_type;
				typedef Compare												key_compare;
				class 	value_compare;
				typedef Alloc												allocator_type;
				typedef typename Alloc::reference							reference;
				typedef typename Alloc::const_reference						const_reference;
				typedef typename Alloc::pointer								pointer;
				typedef typename Alloc::const_pointer						const_pointer;
				typedef AVLtreeIterator<const Key, T, key_compare> 			iterator;
				typedef AVLtreeIterator<const Key, const T, key_compare>	const_iterator;
				typedef ReverseIterator<iterator>			reverse_iterator;
				typedef ReverseIterator<const_iterator>	const_reverse_iterator;
				typedef size_t												size_type;
				typedef std::ptrdiff_t										difference_type;

				class value_compare : public binary_function<value_type, value_type, bool>
				{
					friend class Multimap;

					protected:
						Compare comp;
						value_compare (Compare c) : comp(c) {}  // constructed with Multimap's comparison object

					public:
						typedef bool		result_type;
						typedef value_type	first_argument_type;
						typedef value_type	second_argument_type;

						bool operator() (const value_type& x, const value_type& y) const
						{
							return comp(x.first, y.first);
						}
				};

				typedef AVLtreeNode<const Key, T> node;

		private:
				AVLtree<const Key, T, key_compare> tree_;
		public:

				/*
				** constructors
				*/
				explicit Multimap(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: tree_(comp, alloc) {};
				
				template <class InputIterator>
				Multimap(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: tree_(first, last, comp, alloc)
				{}

				Multimap(const Multimap &x) : tree_(x.tree_)
				{}

				~Multimap()
				{
					//tree_.clear();
				}

				Multimap& operator=(const Multimap &Multimap)
				{
					tree_ = Multimap.tree_;
					return (*this);
				}
				/*
				** iterators
				*/
				iterator begin()
				{
					return (tree_.begin());
				}

				const_iterator begin() const
				{
					return (tree_.begin());
				}

				iterator end()
				{
					return (tree_.end());
				}

				const_iterator end() const
				{
					return (tree_.end());
				}

				reverse_iterator rbegin()
				{					
					return (tree_.rbegin());
				}

				const_reverse_iterator rbegin() const
				{
					return (tree_.rbegin());
				}

				reverse_iterator rend()
				{
					return (tree_.rend());

				}

				const_reverse_iterator rend() const
				{
					return (tree_.rend());
				}
				/*
				** capacity
				*/
				bool					empty(void) const
				{
					return (tree_.empty());
				}

				size_type				size(void) const
				{
					return (tree_.size());
				}

				size_type				max_size(void) const
				{
					return (tree_.max_size());
				}
				/*
				** Element access
				*/

				iterator insert(const value_type& val)
				{
					return (tree_.insert(val));
				}

				iterator insert(iterator position, const value_type& val)
				{
					return (tree_.insert(position, val));
				}
					
				template <class InputIterator>
				void insert(InputIterator first, InputIterator last)
				{
					tree_.insert(first, last);
				}

    			void erase (iterator position)
				{
					tree_.erase(position);
				}

				size_type erase (const key_type& k)
				{
					return (tree_.erase(k));
				}

				void erase (iterator first, iterator last)
				{
					tree_.erase(first, last);
				}

				void swap (Multimap& x)
				{
					tree_.swap(x.tree_);
				}
				void clear()
				{
					tree_.clear();
				}
				/*
				** observers
				*/
				key_compare key_comp() const
				{
					return (tree_.key_comp());
				}

				value_compare value_comp() const
				{
					return (value_compare(key_comp()));
					//return (tree_.value_comp());
				}
				/*
				** operations
				*/
				iterator find (const key_type& k)
				{
					return (tree_.find(k));
				}
				const_iterator find (const key_type& k) const
				{
					return (tree_.find(k));
				}

				size_type count (const key_type& k) const
				{
					return (tree_.count(k));

				}

				iterator	lower_bound(const key_type& k)
				{
					return (tree_.lower_bound(k));
				}

				const_iterator	lower_bound(const key_type& k) const
				{
					return (tree_.lower_bound(k));
				}

				iterator	upper_bound(const key_type& k)
				{
					return (tree_.upper_bound(k));
				}

				const_iterator	upper_bound(const key_type& k) const
				{
					return (tree_.upper_bound(k));
				}

				pair<iterator, iterator> equal_range(const key_type& k)
				{
					return (tree_.equal_range(k));
				}

				pair<const_iterator, const_iterator> equal_range(const key_type& k) const
				{
					return (tree_.equal_range(k));

				}
	};

};

#endif