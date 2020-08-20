#include "List.hpp"
#include <string>
#include <iostream>
#include <list>

int main()
{
	ft::List<int> my_list1;
	std::list<int> list;

	std::cout << my_list1.size() << std::endl;
	std::cout << my_list1.empty() << std::endl;

	for (int i = 1; i <= 5; ++i)
	{
		my_list1.push_back(i);
		ft::List<int>::iterator it = my_list1.begin();
    	std::cout << '<' << *it << '>';
		std::cout << '\n';
	}
	
	for (ft::List<int>::iterator it = my_list1.begin(); it != my_list1.end(); ++it)
    	std::cout << '<' << *it << '>';
  	std::cout << '\n';
	return (0);
}