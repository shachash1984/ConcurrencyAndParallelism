#include <iostream>
#include <future>
#include <thread>
#include <list>
#include <atomic>

using namespace std;

class List 
{
	class Node
	{
		int _data;
		Node* _next;
	public:
		Node(int data, Node* next)
			:_data(data), _next(next)
		{}
		Node* getNext() const
		{
			return _next;
		}
	};

	atomic<Node*> _head;

public:
	List() : _head(nullptr)
	{}
	void push(int data)
	{
		Node* oldhead = _head.load();
		Node* node = new Node(data, oldhead);
		_head.store(node);
	}
	bool empty() const
	{
		return _head.load() == nullptr;
	}
	void pop()
	{
		Node* top = _head.load();
		_head = _head.load()->getNext();
		delete top;
		
	}
};

//void main()
//{
//	List list;
//	std::list<future<void>> futures;
//	for (int i = 0; i < 20000; ++i)
//	{
//		futures.emplace_front(async(launch::async, [&list](int i)
//		{
//			list.push(i);
//		}, i));
//	}
//	while (!futures.empty())
//	{
//		futures.back().get();
//		futures.pop_back();
//	}
//	int len = 0;
//	while (!list.empty())
//	{
//		++len;
//		list.pop();
//	}
//	cout << len << endl;
//}
