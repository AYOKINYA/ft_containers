#include "Vector.hpp"
#include <iostream>


template <class T>
void iter_print(ft::Vector<T> &vector)
{
	typedef typename ft::Vector<T>::iterator iter;
	typedef typename ft::Vector<T>::reverse_iterator reverse_iter;
	
	std::cout << "with iterator :";
	for (iter it = vector.begin(); it != vector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	
	std::cout << "with reverse_iterator :";
	for (reverse_iter it = vector.rbegin(); it != vector.rend(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}


int main (void)
{
	std::cout << "======constructor==========" << std::endl;
	// constructors used in the same order as described above:

	ft::Vector<int> first;                                // empty vector of ints
	std::cout << "Empty : " << std::boolalpha << first.empty() << std::endl;
	std::cout << "size : " << std::boolalpha << first.size() << std::endl;
	ft::Vector<int> second ((unsigned int)4,100);                       // four ints with value 100
	std::cout << "Empty : " << std::boolalpha << second.empty() << std::endl;
	std::cout << "size : " << std::boolalpha << second.size() << std::endl;

	iter_print(second);
	ft::Vector<int> third (second.begin(),second.end());  // iterating through second
	iter_print(third);
	ft::Vector<int> fourth (third);                       // a copy of third
	iter_print(fourth);
	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	ft::Vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (ft::Vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "======resize & size & capcity ==========" << std::endl;

	ft::Vector<int> myvector;
	for (int i=1;i<10;i++)
		myvector.push_back(i);
	std::cout << "size: " << (int) myvector.size() << '\n';
	std::cout << "capacity: " << (int) myvector.capacity() << '\n';
	std::cout << "max_size: " << (int) myvector.max_size() << '\n';
	
	iter_print(myvector);
	myvector.resize(5);
	iter_print(myvector);
	myvector.resize(8,100);
	iter_print(myvector);
	myvector.resize(12);
	iter_print(myvector);

	std::cout << "myvector contains:";
	for (unsigned int i=0;i<myvector.size();i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	std::cout << "======reserve==========" << std::endl;
	ft::Vector<int>::size_type sz;

	ft::Vector<int> x;
	sz = x.capacity();
	std::cout << "making x grow:\n";
	for (int i=0; i<100; ++i) 
	{
		x.push_back(i);
		if (sz != x.capacity()) 
		{
			sz = x.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	ft::Vector<int> y;
	sz = y.capacity();
	y.reserve(100);   // this is the only difference with x above
	std::cout << "making y grow:\n";
	for (int i=0; i<100; ++i) {
		y.push_back(i);
		if (sz != y.capacity()) 
		{
			sz = y.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
    }
	std::cout << "=======operator []=========" << std::endl;

	ft::Vector<int> vec(10);
	ft::Vector<int>::size_type sz2 = vec.size();
	for (unsigned i=0; i < sz2; i++) 
		vec[i] = i;
	for (unsigned i=0; i < sz2 / 2; i++)
	{
		int temp;
		temp = vec[sz2-1-i];
		vec[sz2-1-i] = vec[i];
		vec[i]=temp;
	}

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < sz2; i++)
		std::cout << ' ' << vec[i];
	std::cout << '\n';

	std::cout << "=======at=========" << std::endl;
	for (unsigned i = 0 ; i< vec.size(); i++)
    	vec.at(i) = i;
	std::cout << "myvector contains:";
	for (unsigned i = 0; i < sz2; i++)
		std::cout << ' ' << vec.at(i);
	std::cout << '\n';
	try
	{
		vec.at(-1);
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << "=======front & back & push_back & pop_back=========" << std::endl;
	iter_print(vec);
	std::cout << "front : " << vec.front() << std::endl;
	std::cout << "back : " << vec.back() << std::endl;
	vec.push_back(123);
	iter_print(vec);
	vec.pop_back();
	iter_print(vec);


	
	std::cout << "=======front & back & push_back & pop_back=========" << std::endl;
	
	ft::Vector<int> vec1;
	ft::Vector<int> vec2;
	ft::Vector<int> vec3;

	vec1.assign ((unsigned int)7,100);             // 7 ints with a value of 100
	iter_print(vec1);
	ft::Vector<int>::iterator it;
	it = vec1.begin() + 1;

	vec2.assign (it, vec1.end() - 1); // the 5 central values of first
	iter_print(vec2);

	int myints2[] = {1776,7,4};
	vec3.assign (myints2 , myints2 + 3);   // assigning from array.
	iter_print(vec3);

	std::cout << "Size of first: " << int (vec1.size()) << '\n';
	std::cout << "Size of second: " << int (vec2.size()) << '\n';
	std::cout << "Size of third: " << int (vec3.size()) << '\n';

	std::cout << "========erase=========" << std::endl;
	iter_print(vec);
	vec.erase(vec.begin() + 5);
	iter_print(vec);
	vec.erase(vec.begin(), vec.begin() + 3);
	iter_print(vec);

	std::cout << "========swap=========" << std::endl;
	
	ft::Vector<int> a((unsigned int)3, 100);
	std::cout << "a: ";
	iter_print(a);
	ft::Vector<int> b((unsigned int)5, 200);
	a.swap(b);
	std::cout << "a: ";
	iter_print(a);

	std::cout << "========swap=========" << std::endl;

	ft::Vector<int> foo ((unsigned int)3,100);   // three ints with a value of 100
	ft::Vector<int> bar ((unsigned int)2,200);   // two ints with a value of 200

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

	
	return (0);
}