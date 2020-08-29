#include <iostream>
#include "Deque.hpp"


template <class T>
void iter_print(ft::Deque<T> &deque)
{
	typedef typename ft::Deque<T>::iterator iter;
	typedef typename ft::Deque<T>::reverse_iterator reverse_iter;
	
	std::cout << "with iterator :";
	for (iter it = deque.begin(); it != deque.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	
	std::cout << "with reverse_iterator :";
	for (reverse_iter it = deque.rbegin(); it != deque.rend(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

int main(void)
{
	std::cout << "=======Constructor and assignation operator=========" << std::endl;

	ft::Deque<int> first;                                // empty deque of ints
	std::cout << "size : " << std::boolalpha << first.size() << std::endl;
	std::cout << "Empty? : " << std::boolalpha << first.empty() << std::endl;	
	ft::Deque<int> second ((unsigned int)4,100);                       // four ints with value 100
	ft::Deque<int> third (second.begin(),second.end());  // iterating through second
	ft::Deque<int> fourth (third);

	first = second;
	
	std::cout << "==first contains==\n";
	std::cout << "size : " << std::boolalpha << first.size() << std::endl;
	std::cout << "max_size : " << std::boolalpha << first.max_size() << std::endl;
	std::cout << "Empty? : " << std::boolalpha << first.empty() << std::endl;
	
	iter_print(first);
	std::cout << "==second contains==\n";
	iter_print(second);
	std::cout << "==third contains==\n";
	iter_print(third);
	std::cout << "==fourth contains==\n";
	iter_print(fourth);

	std::cout << "=======resize, back, front, pushback, pushfront=========" << std::endl;
	ft::Deque<int> deque1;
	for (int i=1; i<10; ++i)
		deque1.push_back(i);
	iter_print(deque1);
	deque1.resize(5);
	iter_print(deque1);
	deque1.resize(8,100);
	iter_print(deque1);
	deque1.resize(12);
	iter_print(deque1);
	std::cout << "back: " << deque1.back() << std::endl;
	std::cout << "front: " << deque1.front() << std::endl;
	std::cout << "2th elem " << deque1.at(1) << std::endl;
	std::cout << "3th elem " << deque1[2] << std::endl;
	try
	{
		std::cout << "1000th elem " << deque1.at(1000) << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << "push -1 to the front" << std::endl;
	deque1.push_front(-1);
	std::cout << "front: " << deque1.front() << std::endl;
	
	std::cout << "pop -1 from the front" << std::endl;
	deque1.pop_front();
	std::cout << "front: " << deque1.front() << std::endl;

	std::cout << "push 1234 to the back" << std::endl;
	deque1.push_back(1234);
	std::cout << "front: " << deque1.back() << std::endl;
	
	std::cout << "pop -1 from the back" << std::endl;
	deque1.pop_back();
	std::cout << "front: " << deque1.back() << std::endl;

	std::cout << "===============assign============" << std::endl;
	std::cout << "BEFORE : Size of second: " << int (second.size()) << '\n';
	second.assign((unsigned int)7, 100);
	std::cout << "AFTER : Size of second: " << int (second.size()) << '\n';

	std::cout << "===============swap============" << std::endl;
	ft::Deque<int> foo ((unsigned int)3,100);   // three ints with a value of 100
  	ft::Deque<int> bar ((unsigned int)5,200);   // five ints with a value of 200
	std::cout << "foo contains ";
	iter_print(foo);
	std::cout << "bar contains ";
	iter_print(bar);
	foo.swap(bar);
	std::cout << "foo contains ";
	iter_print(foo);
	std::cout << "bar contains ";
	iter_print(bar);

	std::cout << "========relational operators========" << std::endl;
	foo.swap(bar);
	if (foo == bar) std::cout << "foo and bar are equal\n";
	if (foo != bar) std::cout << "foo and bar are not equal\n";
	if (foo < bar) std::cout << "foo is less than bar\n";
	if (foo > bar) std::cout << "foo is greater than bar\n";
	if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
	if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
	
	std::cout << "===============================" << std::endl;

	return (0);
}