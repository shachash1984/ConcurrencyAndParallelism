#ifndef _SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING
#define _SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING

#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <future>
#include <thread>
#include <deque>

using namespace std::tr2::sys;
using namespace std;

template<class T>
class MessageQueue
{
public:
	void send(T message)
	{
		lock_guard<mutex> lck(_mtx);
		_messages.push_back(move(message));
		_cond.notify_one();
	}
	T receive()
	{
		unique_lock<mutex> lck(_mtx);
		_cond.wait(lck, [this] {return !_messages.empty(); });
		T message = move(_messages.back());
		_messages.pop_back();
		return message;
	}
private:
	deque<T> _messages;
	mutable mutex _mtx;
	mutable condition_variable _cond;
};


//void main()
//{
//	MessageQueue<int> queue;
//	future<void> fut = async([&queue] {queue.send(44); });
//	int i = queue.receive();
//	cout << "Received: " << i << endl;
//	fut.wait();
//}

#endif // !_SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING