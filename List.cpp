#include "List.hpp"
#include <string>
#include <iostream>
#include <list>

int main()
{
	ft::List<int> my_list1;

	std::cout << "======== size & empty ===========" << std::endl;

	std::cout << "size : " << my_list1.size() << std::endl;
	std::cout << "empty? : " << std::boolalpha << my_list1.empty() << std::endl;

	std::cout << "========= push_back & push_front ==========" << std::endl;

	for (int i = 1; i <= 5; ++i)
		my_list1.push_back(i);

	my_list1.push_front(0);
	std::cout << "size : " << my_list1.size() << std::endl;
	std::cout << "empty? : " << std::boolalpha << my_list1.empty() << std::endl;

	std::cout << "========= List constructor ==========" << std::endl;


	ft::List<int> my_list2(my_list1);
	
	for (ft::List<int>::iterator it = my_list2.begin(); it != my_list2.end(); ++it)
    	std::cout << '<' << *it << '>';
  	std::cout << '\n';
	
	ft::List<int> my_list3((unsigned int)3, 5);
	for (ft::List<int>::iterator it = my_list3.begin(); it != my_list3.end(); ++it)
    	std::cout << '<' << *it << '>';
  	std::cout << '\n';

	ft::List<int> my_list4(my_list3.begin(), my_list3.end());
	for (ft::List<int>::iterator it = my_list4.begin(); it != my_list4.end(); ++it)
    	std::cout << '<' << *it << '>';
  	std::cout << '\n';


	std::cout << "========= iter & rev_iter ==========" << std::endl;
	for (ft::List<int>::iterator it = my_list1.begin(); it != my_list1.end(); ++it)
    	std::cout << '<' << *it << '>';
  	std::cout << '\n';

	ft::List<int>::iterator from(my_list1.begin());
	ft::List<int>::iterator until(my_list1.end());
	
	ft::List<int>::reverse_iterator rev_begin(until);
	ft::List<int>::reverse_iterator rev_end(from);

	while (rev_begin != rev_end)
		std::cout << '<' << *(rev_begin++) << '>';
	std::cout << '\n';

    rev_begin = until;
	rev_end = from;
	
	for (int i = 0; i < 6; ++i)
	{
		rev_end -= 1;
		std::cout << '<' << *rev_end << '>';
	}
	std::cout << '\n';
	for (int i = 0; i < 6; ++i)
	{
		std::cout << '<' << *rev_begin << '>';
		rev_begin += 1;
	}
	std::cout << '\n';

	for (ft::List<int>::reverse_iterator rit = my_list1.rbegin(); rit != my_list1.rend(); ++rit)
		std::cout << " " << *rit;
	std::cout << '\n';

	std::cout << "======== front & back ===========" << std::endl;
	std::cout << "my_list1 front is : " << my_list1.front() << std::endl;
	std::cout << "my_list1 back is : " << my_list1.back() << std::endl;

	std::cout << "========pop_back===========" << std::endl;
	
	while (!my_list1.empty())
	{
		std::cout << my_list1.front() << std::endl;
		my_list1.pop_front();
	}
	std::cout << "========pop_back===========" << std::endl;

	std::cout << "========= assign ==========" << std::endl;

	// ft::List<int> my_list5;
	// my_list5.assign(my_list1.begin(), my_list1.end());

	// std::list<int> first;
	// std::list<int> second;
	// first.assign(7, 10);
	// second.assign(first.begin(), first.end());
	// int myints[] = {1776, 7, 4};
  	// first.assign (myints, myints + 3);

	// std::cout << "Size of first: " << first.size() << std::endl;
	// std::cout << "Size of second: " << second.size() << std::endl;

	return (0);
}