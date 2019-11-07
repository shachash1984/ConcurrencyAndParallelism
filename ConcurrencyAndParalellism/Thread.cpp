#include <thread>
#include <iostream>

void threadFun()
{
	std::cout << "Hello from Thread!\n";
}

//int main()
//{
//	std::thread t(threadFun);
//	std::cout << "Hello from main!\n";
//	t.join();
//	return 0;
//}