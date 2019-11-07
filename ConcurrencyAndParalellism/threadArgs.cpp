#include <thread>
#include <iostream>
#include <vector>

using namespace std;

class FunObj
{
public:
	FunObj(int i) : _i(i) {}
	void operator()()
	{
		cout << "Hello from thread!\n";
	}

private:
	int _i;
};

//int main()
//{
//	vector<thread> threads;
//	for (size_t i = 0; i < 16; i++)
//	{
//		threads.emplace_back(FunObj(i));
//
//	}
//	cout << "Hello from main!\n";
//	for (auto& t : threads)
//		t.join();
//	return 0;
//}