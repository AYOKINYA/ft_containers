#include "Multiset.hpp"
#include <iostream>

template <typename T>
void	iter_print(ft::Multiset<T> mset)
{
	std::cout << "in ascending order:";
  	for (ft::Multiset<int>::iterator it=mset.begin(); it!=mset.end(); ++it)
    	std::cout << ' ' << *it;
	std::cout << "\n";
	std::cout << "in reverse order:";
	for (ft::Multiset<int>::reverse_iterator it=mset.rbegin(); it!=mset.rend(); ++it)
			std::cout << ' ' << *it;
	std::cout << "\n";
}

int main(void)
{
	int myints[]= {10,20,30,40,50};
	ft::Multiset<int> first(myints, myints + 5);

	ft::Multiset<int> second;
	std::cout << std::boolalpha << "Empty? : " << second.empty() << std::endl;
	std::cout << "Size : " << second.size() << std::endl;
	std::cout << "max Size : " << second.max_size() << std::endl;

	std::cout << std::boolalpha << "Empty? : " << first.empty() << std::endl;
	std::cout << "Size : " << first.size() << std::endl;
	std::cout << "max Size : " << first.max_size() << std::endl;
	std::cout << "====myset contains===\n";
	iter_print(first);

	ft::Multiset<int> third(first);                  // a copy of second
	iter_print(third);
  	ft::Multiset<int> fourth(first.begin(), first.end());  // iterator ctor.
	iter_print(fourth);
	
	std::cout << "=========insert & erase===========\n";
	ft::Multiset<int> myset;
	ft::Multiset<int>::iterator it;
	ft::pair<ft::Multiset<int>::iterator,bool> ret;

	// set some initial values:
	// for (int i=1; i<=5; ++i)
	// 	myset.insert(i * 10);    // set: 10 20 30 40 50
	// iter_print(myset);

	// it = myset.insert(25);
	// it = myset.insert(it , 27);
	// it = myset.insert(it , 29);
	// it = myset.insert(it , 24);

	// int myints2[]= {5,10,15};              // 10 already in set, not inserted
	// myset.insert (myints2 , myints2 + 3);
	// iter_print(myset);

	// it = myset.begin();
	// ++it;
	// myset.erase(it); // delete 10
	// myset.erase(15); // delete 15
	// it = myset.find(40);
	// myset.erase(it, myset.end()); // delete 40, 50
	// std::cout << "delete 10, 15, 40, 50" << std::endl;
	// iter_print(myset);
	
	// std::cout << "======swap=====" << std::endl;
	// std::cout << "BEFORE myset contains : \n";
	// iter_print(myset);
	// std::cout << "BEFORE fourth contains : \n";
	// iter_print(fourth);
	// myset.swap(fourth);
	// std::cout << "AFTER myset contains : \n";
	// iter_print(myset);
	// std::cout << "AFTER fourth contains : \n";
	// iter_print(fourth);

	// std::cout << "======key_comp && value_comp=====" << std::endl;

	// int highest = *myset.rbegin();
	// ft::Multiset<int>::key_compare mycomp = myset.key_comp();
	// it = myset.begin();
	// do 
	// {
	// 	std::cout << " " << *it;
	// } while (mycomp(*(++it), highest));
	// std::cout << "\n";
	
	// ft::Multiset<int>::value_compare mycomp2 = myset.value_comp();
	// it = myset.begin();
	// do 
	// {
	// 	std::cout << " " << *it;
	// } while (mycomp2(*(++it), highest));
	// std::cout << "\n";
	
	// std::cout << "======count=====" << std::endl;
	
	// for (int i = 0; i < 10; ++i)
	// {
	// 	std::cout << i * 10;
	// 	if (myset.count(i * 10) != 0)
	// 		std::cout << " is an element of myset.\n";
	// 	else
	// 		std::cout << " isn't an element of myset.\n";
	// }

	// std::cout << "=========lower bound & upper bound & equal range=========\n";
	ft::Multiset<int> x;
	ft::Multiset<int>::iterator itlow,itup;

	for (int i=1; i<=7; ++i)
		x.insert(i * 10); 
	x.insert(30);

	iter_print(x);
	itlow = x.lower_bound(30);
  	itup = x.upper_bound(50);
	std::cout << "hello " << *itlow << std::endl;
	std::cout << "hello " << *itup << std::endl;
	x.erase(itlow, itup);
	// x.erase(30);
	// x.erase(40);
	// x.erase(50);

	iter_print(x);

	// std::cout << "=========================================================\n";
	
	return (0);
}
