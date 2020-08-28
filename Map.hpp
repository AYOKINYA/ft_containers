#ifndef MAP_HPP
# define MAP_HPP
# include "Iterator.hpp"
# include "AVLtree.hpp"
# include <memory>
# include <limits>
# include <iostream>

namespace ft
{
	template <typename Key, typename T, class Compare = less<Key>, typename Alloc = std::allocator<pair<const Key,T>> >
	class Map
	{
		public:
				
				typedef	Key										key_type;
				typedef	T										mapped_type;
				typedef pair<const key_type, mapped_type>		value_type;
				typedef Compare									key_compare;
				class 	value_compare;
				typedef Alloc									allocator_type;
				typedef typename Alloc::reference				reference;
				typedef typename Alloc::const_reference			const_reference;
				typedef typename Alloc::pointer					pointer;
				typedef typename Alloc::const_pointer			const_pointer;
				typedef AVLtreeIterator<Key, T> 				iterator;
				typedef AVLtreeIterator<Key, T>		const_iterator;
				typedef AVLtreeRIterator<Key, T>				reverse_iterator;
				typedef AVLtreeRIterator<Key, T>	const_reverse_iterator;
				typedef size_t									size_type;
				typedef std::ptrdiff_t							difference_type;

				class value_compare : public binary_function<value_type, value_type, bool>
				{
					friend class Map;

					protected:
						Compare comp;
						value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

					public:
						typedef bool		result_type;
						typedef value_type	first_argument_type;
						typedef value_type	second_argument_type;

						bool operator() (const value_type& x, const value_type& y) const
						{
							return comp(x.first, y.first);
						}
				};

				typedef AVLtreeNode<Key, T> node;

		private:
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
						//return (n);
					}
					else if (cmp_(data.first, n->data.first))//(data.first < n->data.first)
					{
						n->left = insert_node(n->left, data);
						n->left->parent = n;
					}
					else if (cmp_(n->data.first, data.first))
					{
						n->right = insert_node(n->right, data);
						n->right->parent = n;
					}
					else
						throw std::range_error("Duplicate!");
					
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
					while (cur->left != NULL)  
						cur = cur->left;  
				
					return cur;  
				}  

				node*	delete_node(node *n, const value_type &data)
				{
					if (n == nullptr)
						return (n);
					if (data.first < n->data.first)
						n->left = delete_node(n->left, data);
					else if (data.first > n->data.first)
						n->right = delete_node(n->right, data);
					else
					{
						if (n->left == nullptr || n->right == nullptr)
						{
							node *tmp = nullptr;
							tmp = n->left ? n->left : n->right;
							
							// no child case n->left == nullptr && n->right == nullptr
							if (tmp == NULL)
							{
								//std::cout << n->data.first  << std::endl;
								tmp = n;
								n = nullptr;
								delete (tmp);
							}
							else // one child case
							{
								node *temp = n;
								n = tmp;
								tmp->parent = temp->parent;
								delete (temp);
							}
						}
						else
						{	// node with two children;
							node *tmp = minValueNode(n->right);
							n->data = tmp->data;
							n->right = delete_node(n->right, tmp->data);
						}
						if (n == nullptr)
							return n;
						setHeight(n);
						int bf = balance_factor(n);
						if (bf > 1 && balance_factor(n->left) >= 0)
							return rotateLL(n);
						if (bf < -1 && balance_factor(n->right) < 0)
							return rotateRR(n);
						if (bf > 1 && balance_factor(n->left) < 0)
							return rotateLR(n);
						if (bf < -1 && balance_factor(n->right) > 0)
							return rotateRL(n);
					}
					return (n);
				}

				void free_tree(node* n)
				{
					if (!n)
						return ;
					free_tree(n->left);
					free_tree(n->right);
					delete n;
					n = nullptr;
				}

		public:
				allocator_type	alloc_;
				key_compare		cmp_;
				node*			root_;
				size_type		len_;

				/*
				** constructors
				*/
				explicit Map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: alloc_(alloc), cmp_(comp), root_(nullptr), len_(0)
				{}
				
				template <class InputIterator>
				Map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: alloc_(alloc), cmp_(comp), root_(nullptr), len_(0)
				{
					insert(first, last);
				}

				Map(const Map &x) : alloc_(allocator_type()), cmp_(key_compare()), root_(nullptr), len_(0)
				{
					*this = x;
				}

				~Map()
				{
					clear();
				}

				Map& operator=(const Map &map)
				{
					this->clear();

					this->alloc_ = map.alloc_;
					this->cmp_ = map.cmp_;
					this->root_ = map.root_;
					this->len_ = map.len_;
					
					// deep copy 구현 X. 그냥 insert로 쓰게!	
					// const_iterator it = map.begin();
					// while (it != map.end())
					// {
					// 	insert(begin().getPtr()->data);
					// 	++it;
					// }

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
					node *ret = this->root_;
					while (ret && ret->right)
						ret = ret->right;
					return (reverse_iterator(this->root_, ret));
				}

				const_reverse_iterator rbegin() const
				{
					node *ret = this->root_;
					while (ret && ret->right)
						ret = ret->right;
					return (const_reverse_iterator(this->root_, ret));
				}

				reverse_iterator rend()
				{
					return (reverse_iterator(this->root_, NULL));
				}

				const_reverse_iterator rend() const
				{
					return (const_reverse_iterator(this->root_, NULL));
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
				mapped_type& operator[] (const key_type& k)
				{
					iterator iter = find(k);
					if (iter != end())
						return (iter->second);
					pair<iterator, bool> res = insert(make_pair(k, mapped_type()));
					
					return ((res.first)->second);

				}
				pair<iterator,bool> insert(const value_type& val)
				{
					node *n = insert_node(root_, val);
					n = find(val.first).getPtr();
					// std::cout << val.first << std::endl;
					// std::cout << "1st " << n->data.first << std::endl;
					// std::cout << "2nd " << n->data.second << std::endl;
					++this->len_;
					return (make_pair(iterator(this->root_, n), true));
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
					iterator iter = first;
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
					delete_node(root_, n->data);
					--this->len_;
				}

				size_type erase (const key_type& k)
				{
					node *n;

					n = this->root_;
					while (n)
					{
						if (k == n->data.first)
						{
							delete_node(root_, n->data);
							--this->len_;
							return (1);
						}
						if (cmp_(k, n->data.first))
							n = n->left;
						else
							n = n->right;
					}
					return (0);
				}

				void erase (iterator first, iterator last)
				{
					iterator next;

					while (first != last)
					{
						next = first;
						++next;
						delete_node(root_, *first);
						--this->len_;
						first = next;
					}
				}

				void swap (Map& x)
				{
					std::swap(alloc_, x.alloc_);
					std::swap(cmp_, x.cmp_);
					std::swap(root_, x.root_);
					std::swap(len_, x.len_);
				}
				void clear()
				{
					free_tree(root_);
					this->len_ = 0;
				}
				/*
				** observers
				*/
				key_compare key_comp() const
				{
					return (this->cmp_);
				}

				value_compare value_comp() const
				{
					return (value_compare(key_comp()));
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
						if (cmp_(k, n->data.first))
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
						if (cmp_(k, n->data.first))
							n = n->left;
						else
							n = n->right;
					}
					return (this->end());
				}

				size_type count (const key_type& k) const
				{
					return (find(k) == this->end());
				}

				iterator	lower_bound(const key_type& k)
				{
					iterator start = begin();
					iterator last = end();
					key_compare k_cmp = key_comp();

					while (start != last)
					{
						if (k_cmp((*start).first, k) <= 0)
							return (iterator(this->root_, start.getPtr()));
						++start;
					}
					return (this->end());
				}

				const_iterator	lower_bound(const key_type& k) const
				{
					iterator start = begin();
					iterator last = end();
					key_compare k_cmp = key_comp();

					while (start != last)
					{
						if (k_cmp((*start).first, k) <= 0)
							return (const_iterator(this->root_, start.getPtr()));
						++start;
					}
					return (this->end());
				}

				iterator	upper_bound(const key_type& k)
				{
					iterator start = begin();
					iterator last = end();
					key_compare k_cmp = key_comp();

					while (start != last)
					{
						if ((*start).first == k)
							return (iterator(this->root_, (++start).getPtr()));
						if (k_cmp((*start).first, k) <= 0)
							return (iterator(this->root_, start.getPtr()));
						++start;
					}
					return (this->end());
				}

				const_iterator	upper_bound(const key_type& k) const
				{
					iterator start = begin();
					iterator last = end();
					key_compare k_cmp = key_comp();

					while (start != last)
					{
						if ((*start).first == k)
							return (const_iterator(this->root_, (++start).getPtr()));
						if (k_cmp((*start).first, k) <= 0)
							return (const_iterator(this->root_, start.getPtr()));
						++start;
					}
					return (this->end());
				}

				pair<iterator, iterator> equal_range(const key_type& k)
				{
					return make_pair(lower_bound(k), upper_bound(k));
				}

				pair<const_iterator, const_iterator> equal_range(const key_type& k) const
				{
					return make_pair(lower_bound(k), upper_bound(k));
				}
	};

};

#endif