#ifndef MAP_HPP
# define MAP_HPP
# include "Iterator.hpp"
# include <memory>
# include <limits>
# include <iostream>

namespace ft
{
	template <typename Key, typename T, class Compare = ft::less<Key>, typename Alloc = allocator<ft::pair<const Key,T> >
	class Map
	{
		public:
				typedef	Key	key_type;
				typedef	T	mapped_type;
				typedef ft::pair<const key_type , mapped_type> value_type;
				typedef Compare	key_compare;
				//value_compare??
				typedef Alloc							allocator_type;
				typedef typename Alloc::reference		reference;
				typedef typename Alloc::const_reference	const_reference;
				typedef typename Alloc::pointer			pointer;
				typedef typename Alloc::const_pointer	const_pointer;
				// typedef IteratorMap<Key, T> 					iterator;
				// typedef IteratorMap<const Key, const T>			const_iterator;
				// typedef ReverseIterator<iterator>		reverse_iterator;
				// typedef ReverseIterator<const_iterator>	const_reverse_iterator;
				typedef size_t							size_type;
				typedef std::ptrdiff_t					difference_type;



	};
};