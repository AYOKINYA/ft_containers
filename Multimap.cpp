#include "Multimap.hpp"
#include <iostream>

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp
{
	bool operator() (const char& lhs, const char& rhs) const
	{
		return (lhs < rhs);
	}
};

template <typename Key, typename T>
void	iter_print(ft::Multimap<Key, T> &mmap)
{
	typename ft::Multimap<Key, T>::iterator it = mmap.begin();
	typename ft::Multimap<Key, T>::reverse_iterator rit = mmap.rbegin();

	std::cout << "in ascending order:\n";
  	for (; it!=mmap.end(); ++it)
    	std::cout << it->first << " => " << it->second << '\n';

	std::cout << "in reverse order:\n";
	for (; rit!=mmap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';
}

int main ()
{
	std::cout << "=========Constructor with empty and size===========\n";
	
	ft::Multimap<char , int> first;
	std::cout << std::boolalpha << "Empty? : " << first.empty() << std::endl;
	std::cout << "Size : " << first.size() << std::endl;
	std::cout << "Max_size : " << first.max_size() << std::endl;

	first.insert(ft::pair<char,int>('a',10));
	first.insert(ft::pair<char,int>('b',15));
	first.insert(ft::pair<char,int>('b',20));
	first.insert(ft::pair<char,int>('c',25));
	std::cout << std::boolalpha << "Empty? : " << first.empty() << std::endl;
	std::cout << "Size : " << first.size() << std::endl;
	iter_print(first);

	std::cout << "======insert============\n";
	ft::Multimap<char , int> mmap2;
	ft::Multimap<char,int>::iterator it;
	it = mmap2.insert ( ft::pair<char,int>('a', 10) );
	mmap2.insert ( it, ft::pair<char,int>('b', 20) );

	ft::Multimap<char , int> second(mmap2);
	iter_print(second);

	std::cout << "======swap============\n";
	ft::Multimap<char,int> foo,bar;

	foo.insert(ft::make_pair('x',11));
	foo.insert(ft::make_pair('y',22));

	bar.insert(ft::make_pair('a',100));
	bar.insert(ft::make_pair('b',200));
	bar.insert(ft::make_pair('b',200));
	bar.insert(ft::make_pair('c',300));

	std::cout << "foo contains:\n";
	for (ft::Multimap<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << (*it).first << " => " << (*it).second << '\n';

	std::cout << "bar contains:\n";
	for (ft::Multimap<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << (*it).first << " => " << (*it).second << '\n';
	
	
	std::cout << "=====key_comp=====" << std::endl;
	ft::Multimap<char,int>::key_compare mycomp = bar.key_comp();
	char highest = bar.rbegin()->first;
	it = bar.begin();
	do {
		std::cout << (*it).first << " => " << (*it).second << '\n';
	} while ( mycomp((*it++).first, highest) );

	std::cout << "=====value_comp=====" << std::endl;

	ft::pair<char,int> highest2 = *bar.rbegin();          // last element

	it = bar.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( bar.value_comp()(*it++, highest2) );

	std::cout << "=====count=======" << std::endl;
	
	for (char c='a'; c<='c'; c++)
	{
		std::cout << "There are " << bar.count(c) << " elements with key " << c << ":";
		ft::Multimap<char,int>::iterator it;
		for (it=bar.equal_range(c).first; it!=bar.equal_range(c).second; ++it)
			std::cout << ' ' << (*it).second;
		std::cout << '\n';
	}

	std::cout << "=========lower bound & upper bound & equal range=========\n";

	ft::Multimap<char, int> mmap3;
	ft::Multimap<char, int>::iterator itlow, itup;

	mmap3.insert(ft::make_pair('a',10));
	mmap3.insert(ft::make_pair('b',121));
	mmap3.insert(ft::make_pair('c',1001));
	mmap3.insert(ft::make_pair('c',2002));
	mmap3.insert(ft::make_pair('d',11011));
	mmap3.insert(ft::make_pair('e',44));

	itlow = mmap3.lower_bound ('b');  // itlow points to b
  	itup = mmap3.upper_bound ('d');   // itup points to e (not d)

  	// print range [itlow,itup):
  	for (it=itlow; it!=itup; ++it)
    	std::cout << (*it).first << " => " << (*it).second << '\n';

	std::cout << "==================\n";
	return 0;
}