#include <thread>
#include <iostream>
#include <future>
#include <string>
#include <memory>

std::string fun(bool flag)
{
	if (flag)
	{
		std::cout << "Worker returning.\n";
		return "Message from worker";
	}
	else
	{
		std::cout << "Worker throwing.\n";
		throw std::exception("Exception from thread.");
	}
}

//int main()
//{
//	
//	std::future <std::string> fut = std::async(fun, false);
//	std::cout << "Main receiving:\n";
//	try
//	{
//		std::string s = fut.get();
//		std::cout << s << std::endl;
//	}
//	catch (const std::exception e)
//	{
//		std::cout << "Caught: " << e.what() << std::endl;
//	}
//}
