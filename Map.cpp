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
	ft::Map<char , int> first;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;

	// ft::Map<char , int> second (first.begin(),first.end());

	// ft::Map<char , int> third (second);

	// ft::Map<char, int ,classcomp> fourth;                 // class as Compare

	// bool(*fn_pt)(char,char) = fncomp;
	// ft::Map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	return 0;
}