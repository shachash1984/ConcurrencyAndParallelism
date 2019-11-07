#include <thread>
#include <iostream>
#include <vector>
#include<chrono>

using namespace std;

vector<thread> spawn()
{
	vector<thread> threads;
	for (size_t i = 0; i < 16; i++)
	{
		threads.emplace_back([&] 
		{
			this_thread::sleep_for(chrono::milliseconds(10 * i));
			cout
				<< "Hello from thread " << i << endl;
		});
	}
	return threads;
}

//int main() 
//{
//	vector<thread> threads = spawn();
//	cout << "Hello from main\n";
//	for (auto& t : threads)
//		t.join();
//	return 0;
//}