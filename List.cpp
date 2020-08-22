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

	ft::List<int>::reverse_iterator rit = my_list2.rbegin();
	int i = 0;
	while (i++ < 10 && rit != my_list2.rend())
		std::cout << " " << *rit++;
	std::cout << '\n';

	for (ft::List<int>::reverse_iterator rit = my_list1.rbegin(); rit != my_list1.rend(); ++rit)
		std::cout << " " << *rit;
	std::cout << '\n';
	std::cout << "==================" << std::endl;

	
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

	std::cout << "========pop_front===========" << std::endl;
	
	while (!my_list1.empty())
	{
		std::cout << my_list1.front() << std::endl;
		my_list1.pop_front();
	}

	std::cout << "========pop_back===========" << std::endl;

	while (!my_list2.empty())
	{
		std::cout << my_list2.back() << std::endl;
		my_list2.pop_back();
	}

	std::cout << "========= assign ==========" << std::endl;

	ft::List<int> first;
	ft::List<int> second;
	first.assign((unsigned int)7, 10);
	second.assign(first.begin(), first.end());
	int myints[] = {1776, 7, 4};
  	first.assign (myints, myints + 3);

	std::cout << "Size of first: " << first.size() << std::endl;
	std::cout << "Size of second: " << second.size() << std::endl;

	std::cout << "========= swap ==========" << std::endl;
	
	ft::List<int> a ((unsigned int)3,100);   // three ints with a value of 100
	ft::List<int> b ((unsigned int)5,200);  // five ints with a value of 200

	a.swap(b);

	std::cout << "first contains:";

	for (ft::List<int>::iterator it=a.begin(); it!=a.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (ft::List<int>::iterator it=b.begin(); it!=b.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "========= resize ==========" << std::endl;

	ft::List<int> my_list5;
	for (int i = 1; i < 10; ++i)
		my_list5.push_back(i);

	i = 0;
	for (ft::List<int>::iterator it=my_list5.begin(); it!=my_list5.end(); ++it)
    	std::cout << ' ' << *it;	
	std::cout << '\n';

	my_list5.resize(5);
	for (ft::List<int>::iterator it=my_list5.begin(); it!=my_list5.end(); ++it)
    	std::cout << ' ' << *it;
	std::cout << '\n';

	my_list5.resize(8,100);

	for (ft::List<int>::iterator it=my_list5.begin(); it!=my_list5.end(); ++it)
    	std::cout << ' ' << *it;
	std::cout << '\n';


	my_list5.resize(12);
	for (ft::List<int>::iterator it=my_list5.begin(); it!=my_list5.end(); ++it)
    	std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "========= splice ==========" << std::endl;

	ft::List<int> mylist1, mylist2;
	ft::List<int>::iterator it;

	// set some initial values:
	for (int i=1; i<=4; ++i)
		mylist1.push_back(i);      // mylist1: 1 2 3 4

	for (int i=1; i<=3; ++i)
		mylist2.push_back(i*10);   // mylist2: 10 20 30

	it = mylist1.begin();
	++it;                         // points to 2

	mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
									// mylist2 (empty)
									// "it" still points to 2 (the 5th element)
	std::cout << "mylist1 contains:";
	for (ft::List<int>::iterator iter = mylist1.begin(); iter != mylist1.end(); ++iter)
		std::cout << ' ' << *iter;
	std::cout << '\n';										
	
	std::cout << *it << std::endl;
	
	mylist2.splice(mylist2.begin(), mylist1, it);
									// mylist1: 1 10 20 30 3 4
									// mylist2: 2
	
	std::cout << "mylist1 contains:";
	for (ft::List<int>::iterator iter = mylist1.begin(); iter != mylist1.end(); ++iter)
		std::cout << ' ' << *iter;

	std::cout << '\n';
	std::cout << "mylist2 contains:";
	for (ft::List<int>::iterator iter = mylist2.begin(); iter != mylist2.end(); ++iter)
		std::cout << ' ' << *iter;
	std::cout << '\n';
	
	it = mylist1.begin();
	for (int i = 0; i < 3; ++i)
		++it; //it is pointing 30.

	mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
									// mylist1: 30 3 4 1 10 20
	std::cout << "mylist1 contains:";
	for (ft::List<int>::iterator iter = mylist1.begin(); iter != mylist1.end(); ++iter)
		std::cout << ' ' << *iter;
	std::cout << '\n';

	std::cout << "========= remove ==========" << std::endl;

	return (0);
}