#include <iostream>
#include "Queue.hpp"

int main(void)
{
	ft::List<int> lst((unsigned int)3, 100);

	std::cout << "=====constructor==========" << std::endl;
	ft::Queue<int> q(lst); // Equal to ft::Queue<int, ft::List<int>> s(lst);
	
	std::cout << "q" << std::endl;
	std::cout << "size of first: " << q.size() << '\n';
	std::cout << "Empty? : " << std::boolalpha << q.empty() << '\n';

	std::cout << "q2" << std::endl;
	ft::Queue<int> q2;
	std::cout << "size of first: " << q2.size() << '\n';
	std::cout << "Empty? : " << std::boolalpha << q2.empty() << '\n';
	std::cout << "====q2 = s. assignation operator====" << std::endl;
	q2 = q;
	std::cout << "size of first: " << q2.size() << '\n';
	std::cout << "Empty? : " << std::boolalpha << q2.empty() << '\n';

	std::cout << "=====push 42 & pop gain==========" << std::endl;
	std::cout << q.front() << std::endl;
	std::cout << q.back() << std::endl;

	q.push(42);
	std::cout << "front : "  << q.front() << std::endl;
	std::cout << "back : " << q.back() << std::endl;
	q.pop();
	std::cout << "front : "  << q.front() << std::endl;
	std::cout << "back : " << q.back() << std::endl;
	q.pop();
	std::cout << "front : "  << q.front() << std::endl;
	std::cout << "back : " << q.back() << std::endl;
	q.pop();
	std::cout << "front : "  << q.front() << std::endl;
	std::cout << "back : " << q.back() << std::endl;


	std::cout << "===========relational operators===========" << std::endl;
	
	if (q == q2)
		std::cout << "q == q2" << std::endl;
	if (q != q2)
		std::cout << "q != q2" << std::endl;
	if (q >= q2)
		std::cout << "q >= q2" << std::endl;
	if (q <= q2)
		std::cout << "q <= q2" << std::endl;
	if (q > q2)
		std::cout << "q >= q2" << std::endl;
	if (q < q2)
		std::cout << "q <= q2" << std::endl;
	
	std::cout << "===============================" << std::endl;
	return (0);
}