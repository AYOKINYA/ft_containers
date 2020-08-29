#ifndef MAP_HPP
# define MAP_HPP
# include "Iterator.hpp"
# include "AVLtree.hpp"
# include <memory>
# include <limits>

namespace ft
{
	template <typename Key, typename T, class Compare = std::less<Key>, typename Alloc = std::allocator<pair<const Key,T>> >
	class Map
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

				typedef AVLtreeNode<const Key, T> node;

		private:
				AVLtree<const Key, T, key_compare> tree_;
		public:

				/*
				** constructors
				*/
				explicit Map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: tree_(comp, alloc) {};
				
				template <class InputIterator>
				Map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: tree_(first, last, comp, alloc)
				{}

				Map(const Map &x) : tree_(x.tree_)
				{}

				~Map()
				{
					//tree_.clear();
				}

				Map& operator=(const Map &map)
				{
					tree_ = map.tree_;
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
				mapped_type& operator[] (const key_type& k)
				{
					return (tree_[k]);
				}
				pair<iterator,bool> insert(const value_type& val)
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

				void swap (Map& x)
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