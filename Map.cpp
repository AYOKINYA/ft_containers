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
	std::cout << "=========Constructor===========\n";
	
	ft::Map<char , int> first;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;

	std::cout << first['a'] << '\n';
	std::cout << first['b'] << '\n';
	std::cout << first['c'] << '\n';
	std::cout << first['d'] << '\n';

	for (ft::Map<char,int>::iterator it=first.begin(); it!=first.end(); ++it)
    	std::cout << it->first << " => " << it->second << '\n';
	std::cout << first.rbegin()->data << std::endl;
	// for (ft::Map<char,int>::reverse_iterator it=first.rbegin(); it!=first.rend(); ++it)
    // 	std::cout << it->first << " => " << it->second << '\n';

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

	return 0;
}