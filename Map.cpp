#include "Map.hpp"
#include <iostream>

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp
{
	bool operator() (const char& lhs, const char& rhs) const
	{
		return (lhs < rhs);
	}
};

int main ()
{
	std::cout << "=========Constructor with empty and size===========\n";
	
	ft::Map<char , int> first;
	std::cout << std::boolalpha << "Empty? : " << first.empty() << std::endl;
	std::cout << std::boolalpha << "Size : " << first.size() << std::endl;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;

	std::cout << first['a'] << '\n';
	std::cout << first['b'] << '\n';
	std::cout << first['c'] << '\n';
	std::cout << first['d'] << '\n';

	std::cout << std::boolalpha << "Empty? : " << first.empty() << std::endl;
	std::cout << std::boolalpha << "Size : " << first.size() << std::endl;
	std::cout << "====================\n";

	ft::Map<char , int> second (first.begin(),first.end());

	std::cout << second['a'] << '\n';
	std::cout << second['b'] << '\n';
	std::cout << second['c'] << '\n';
	std::cout << second['d'] << '\n';

	std::cout << "====================\n";

	ft::Map<char , int> third (second);

	std::cout << third['a'] << '\n';
	std::cout << third['b'] << '\n';
	std::cout << third['c'] << '\n';
	std::cout << third['d'] << '\n';
	
	ft::Map<char, int , classcomp> fourth;                 // class as Compare

	bool(*fn_pt)(char,char) = fncomp;
	ft::Map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	std::cout << "=========Iterators=========\n";

	ft::Map<char,int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	std::cout << "print with Itreators :\n";
	for (ft::Map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    	std::cout << it->first << " => " << it->second << '\n';
	std::cout << "print with ReverseItreators :\n";
	for (ft::Map<char,int>::reverse_iterator rit = mymap.rbegin() ; rit != mymap.rend() ; ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';

	std::cout << "=========Erase=========\n";

	ft::Map<char , int> map2;
	
	map2['a']=10;
	map2['b']=20;
	map2['c']=30;
	map2['d']=40;
	map2['e']=50;
	map2['f']=60;
	/*
	**	   b
	**    / \
	**   a   d
	**      / \	
	**	   c	e
	**			 \
	**			  f
	*/
	ft::Map<char,int>::iterator it;
	
	// when no child
	std::cout << "when no child" << std::endl;
	ft::Map<char , int> map1(map2);
	map1.erase('c');                  // erasing by key
	for (it=map1.begin(); it!=map1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	for (ft::Map<char,int>::reverse_iterator it=map1.rbegin(); it!=map1.rend(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	// when one child
	std::cout << "when one child" << std::endl;

	ft::Map<char , int> map3(map2);
	map3.erase('e');                    // erasing by key

	for (it=map3.begin(); it!=map3.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	for (ft::Map<char,int>::reverse_iterator it=map3.rbegin(); it!=map3.rend(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	
	// when two children
	std::cout << "when two children" << std::endl;

	ft::Map<char , int> map4(map2);
	map4.erase('d');                    // erasing by key

	for (it=map4.begin(); it!=map4.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	for (ft::Map<char,int>::reverse_iterator it=map4.rbegin(); it!=map4.rend(); ++it)
		std::cout << it->first << " => " << it->second << '\n';


	// show content:

	return 0;
}