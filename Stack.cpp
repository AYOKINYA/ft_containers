#include <iostream>
#include "Stack.hpp"

int main(void)
{
	ft::List<int> lst((unsigned int)3, 100);

	std::cout << "=====constructor==========" << std::endl;
	ft::Stack<int> s(lst); // Equal to ft::Stack<int, ft::List<int>> s(lst);
	std::cout << "size of first: " << s.size() << '\n';
	std::cout << "Empty? : " << std::boolalpha << s.empty() << '\n';

	ft::Stack<int> s2;
	std::cout << "=====push & pop==========" << std::endl;
	std::cout << s.top() << std::endl;
	s.push(42);
	std::cout << s.top() << std::endl;


	return (0);
}