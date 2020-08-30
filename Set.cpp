#include <iostream>
#include "Set.hpp"

template <typename T>
void	iter_print(ft::Set<T> set)
{
	std::cout << "in ascending order:";
  	for (ft::Set<int>::iterator it=set.begin(); it!=set.end(); ++it)
    	std::cout << ' ' << *it;
	std::cout << "\n";
	std::cout << "in reverse order:";
	for (ft::Set<int>::reverse_iterator it=set.rbegin(); it!=set.rend(); ++it)
			std::cout << ' ' << *it;
	std::cout << "\n";
}

int main(void)
{
	std::cout << "=========Constructor with empty and size===========\n";
	
	int myints[]= {10,20,30,40,50};
	ft::Set<int> first(myints, myints + 5);

	ft::Set<int> second;
	std::cout << std::boolalpha << "Empty? : " << second.empty() << std::endl;
	std::cout << "Size : " << second.size() << std::endl;
	std::cout << "max Size : " << second.max_size() << std::endl;

	std::cout << std::boolalpha << "Empty? : " << first.empty() << std::endl;
	std::cout << "Size : " << first.size() << std::endl;
	std::cout << "max Size : " << first.max_size() << std::endl;
	std::cout << "====myset contains===\n";
	iter_print(first);

	ft::Set<int> third(first);                  // a copy of second
	iter_print(third);
  	ft::Set<int> fourth(first.begin(), first.end());  // iterator ctor.
	iter_print(fourth);


	std::cout << "=========insert & erase===========\n";
	ft::Set<int> myset;
	ft::Set<int>::iterator it;
	ft::pair<ft::Set<int>::iterator,bool> ret;

	// set some initial values:
	for (int i=1; i<=5; ++i)
		myset.insert(i * 10);    // set: 10 20 30 40 50
	iter_print(myset);

	ret = myset.insert(20);               // no new element inserted
	
	iter_print(myset);

	if (ret.second == false)
		it = ret.first;  // "it" now points to element 20

	myset.insert(it , 25);                 // max efficiency inserting
	myset.insert(it , 24);                 // max efficiency inserting
	myset.insert(it , 26);                 // no max efficiency inserting
	iter_print(myset);

	int myints2[]= {5,10,15};              // 10 already in set, not inserted
	myset.insert (myints2 , myints2 + 3);
	iter_print(myset);

	it = myset.begin();
	++it;
	myset.erase(it); // delete 10
	myset.erase(15); // delete 15
	it = myset.find(40);
	myset.erase(it, myset.end()); // delete 40, 50
	std::cout << "delete 10, 15, 40, 50" << std::endl;
	iter_print(myset);
	

	std::cout << "======swap=====" << std::endl;
	std::cout << "BEFORE myset contains : \n";
	iter_print(myset);
	std::cout << "BEFORE fourth contains : \n";
	iter_print(fourth);
	myset.swap(fourth);
	std::cout << "AFTER myset contains : \n";
	iter_print(myset);
	std::cout << "AFTER fourth contains : \n";
	iter_print(fourth);
	
	std::cout << "======key_comp && value_comp=====" << std::endl;

	int highest = *myset.rbegin();
	ft::Set<int>::key_compare mycomp = myset.key_comp();
	it = myset.begin();
	do 
	{
		std::cout << " " << *it;
	} while (mycomp(*(++it), highest));
	std::cout << "\n";
	
	ft::Set<int>::value_compare mycomp2 = myset.value_comp();
	it = myset.begin();
	do 
	{
		std::cout << " " << *it;
	} while (mycomp2(*(++it), highest));
	std::cout << "\n";
	
	std::cout << "======count=====" << std::endl;
	
	for (int i = 0; i < 10; ++i)
	{
		std::cout << i * 10;
		if (myset.count(i * 10) != 0)
			std::cout << " is an element of myset.\n";
		else
			std::cout << " isn't an element of myset.\n";
	}

	std::cout << "=========lower bound & upper bound & equal range=========\n";

	ft::Set<int>::iterator itlow,itup;
	iter_print(myset);
	itlow = myset.lower_bound(20);
  	itup = myset.upper_bound(40);
	std::cout << "hello " << *itlow << std::endl;
	std::cout << "hello " << *itup << std::endl;
	myset.erase(itlow, itup);
	iter_print(myset);

	std::cout << "=========================================================\n";

	return (0);
}