#include <iostream>
#include "Stack.hpp"

int main(void)
{
	ft::List<int> lst((unsigned int)3, 100);

	std::cout << "=====constructor==========" << std::endl;
	ft::Stack<int> s(lst); // Equal to ft::Stack<int, ft::List<int>> s(lst);
	
	std::cout << "s" << std::endl;
	std::cout << "size of first: " << s.size() << '\n';
	std::cout << "Empty? : " << std::boolalpha << s.empty() << '\n';

	std::cout << "s2" << std::endl;
	ft::Stack<int> s2;
	std::cout << "size of first: " << s2.size() << '\n';
	std::cout << "Empty? : " << std::boolalpha << s2.empty() << '\n';
	std::cout << "====s2 = s. assignation operator====" << std::endl;
	s2 = s;
	std::cout << "size of first: " << s2.size() << '\n';
	std::cout << "Empty? : " << std::boolalpha << s2.empty() << '\n';

	std::cout << "=====push 42 & pop gain==========" << std::endl;
	std::cout << s.top() << std::endl;
	s.push(42);
	std::cout << s.top() << std::endl;
	s.pop();
	std::cout << s.top() << std::endl;

	std::cout << "===========relational operators===========" << std::endl;
	
	if (s == s2)
		std::cout << "s == s2" << std::endl;
	if (s != s2)
		std::cout << "s != s2" << std::endl;
	if (s >= s2)
		std::cout << "s >= s2" << std::endl;
	if (s <= s2)
		std::cout << "s <= s2" << std::endl;
	if (s > s2)
		std::cout << "s >= s2" << std::endl;
	if (s < s2)
		std::cout << "s <= s2" << std::endl;
	
	std::cout << "===============================" << std::endl;
	
	return (0);
}