#include <thread>
#include <iostream>
#include <future>
#include <memory>

struct Counter
{
	Counter(int k) : n(k){}
	int n;
};

//void main()
//{
//	Counter * pCount = new Counter(10);
//	std::unique_ptr<Counter> puCount(pCount);
//	std::future<void> fut = std::async([](std::unique_ptr<Counter> p)
//	{
//		++(p->n);
//	}, std::move(puCount));
//	std::cout << pCount->n << std::endl;
//	fut.wait();
//}