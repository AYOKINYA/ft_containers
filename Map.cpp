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

	//ft::Map<char , int> third (second);

	// std::cout << third['a'] << '\n';
	// std::cout << third['b'] << '\n';
	// std::cout << third['c'] << '\n';
	// std::cout << third['d'] << '\n';
	
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
	**	   d
	**    / \
	**   b   e
	**  / \   \	
	** a   c   f
	*/
	
	ft::Map<char,int>::iterator it;
	
	// when no child
	std::cout << "when no child" << std::endl;
	ft::Map<char , int> map1;

	map1.insert(map2.begin(), map2.end());
    map1.erase('c');                  // erasing by key
	for (it=map1.begin(); it!=map1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	for (ft::Map<char,int>::reverse_iterator it=map1.rbegin(); it!=map1.rend(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	//when one child
	std::cout << "when one child" << std::endl;

	ft::Map<char , int> map3;
	map3.insert(map2.begin(), map2.end());
	map3.erase('e');                    // erasing by key
	for (it=map3.begin(); it!=map3.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	for (ft::Map<char,int>::reverse_iterator it=map3.rbegin(); it!=map3.rend(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	
	// when two children
	std::cout << "when two children" << std::endl;

	ft::Map<char , int> map4;
	map4.insert(map2.begin(), map2.end());
	map4.erase('d');                    // erasing by key

	for (it=map4.begin(); it!=map4.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	for (ft::Map<char,int>::reverse_iterator it=map4.rbegin(); it!=map4.rend() ; ++it)
		std::cout << it->first << " => " << it->second << '\n';

	ft::Map<char , int> map5;
	map5.insert(map2.begin(), map2.end());
	
	it = map5.find('b');
	for (ft::Map<char,int>::iterator iter=map5.begin(); iter!=map5.end(); ++iter)
		std::cout << iter->first << " => " << iter->second << '\n';
	map5.erase (it);                   // erasing by iterator

	map5.erase ('c');                  // erasing by key

	it=map5.find ('e');
	map5.erase ( it, map5.end() );    // erasing by range

	std::cout << "multiple erase" << std::endl;
	for (it=map5.begin(); it!=map5.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "=========swap=========\n";

	std::cout << "map1 contains : \n";
	for (it=map1.begin(); it!=map1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "map5 contains : \n";
	for (it=map5.begin(); it!=map5.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	map1.swap(map5);
	std::cout << "map1 contains : \n";
	for (it=map1.begin(); it!=map1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "map5 contains : \n";
	for (it=map5.begin(); it!=map5.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	
	std::cout << "=========key compare=========\n";

	ft::Map<char,int> map6;

	ft::Map<char,int>::key_compare mycomp = map6.key_comp();

	map6['a']=100;
	map6['b']=200;
	map6['c']=300;

	std::cout << "map6 contains:\n";

	char highest = map6.rbegin()->first;     // key value of last element

	it = map6.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mycomp((*it++).first, highest) );

	std::cout << "=========value compare=========\n";
	ft::pair<char,int> highest2 = *map6.rbegin();          // last element

	it = map6.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( map6.value_comp()(*it++, highest2) );

	std::cout << "=========count=========\n";
	char c;
	for (c= 'a'; c < 'h'; c++)
	{
		std::cout << c;
		if (map6.count(c) > 0)
			std::cout << " is an element of mymap.\n";
		else 
			std::cout << " is not an element of mymap.\n";
	}

	std::cout << "=========lower bound & upper bound & equal range=========\n";
	std::cout << "map contains:\n";
	for (it=map2.begin(); it!=map2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	ft::Map<char, int>::iterator itlow, itup;

	itlow = map2.lower_bound('b');
	itup = map2.upper_bound('d');
	map2.erase(itlow, itup);
	std::cout << "output\n";

	for (it=map2.begin(); it!=map2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	
	ft::pair<ft::Map<char,int>::iterator,ft::Map<char,int>::iterator> ret;
  	ret = map2.equal_range('e');
	
	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';

	std::cout << "==================\n";

	return 0;
}