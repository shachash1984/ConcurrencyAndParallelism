#ifndef _SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING
#define _SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING

#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <future>
#include <thread>

using namespace std::tr2::sys;
using namespace std;

class FileMonitor1
{
public:
	void push_back(string file)
	{
		lock_guard<mutex> lck(_mtx);
		_counter++;
		_allFiles.push_back(move(file));
	}
	bool hasData() const
	{
		lock_guard<mutex> lck(_mtx);
		return !_allFiles.empty();
	}
	string pop_back()
	{
		lock_guard<mutex> lck(_mtx);
		string name = move(_allFiles.back());
		_allFiles.pop_back();
		_counter--;
		return name;
	}
	bool isDone() 
	{
		return _counter == 0;
	}
private:
	vector<string> _allFiles;
	mutable mutex _mtx;
	int _counter;
};

void listDir(string path, FileMonitor1& fileSink)
{
	for (directory_iterator it(path); it != directory_iterator(); ++it)
	{
		if (is_regular_file(it->status()))
		{
			size_t temp = hash<thread::id>{}(this_thread::get_id());
			string str = to_string(temp);
			str += " ***";
			str += it->path().string();
			fileSink.push_back(str);
		}
	}
}

void listDirs(vector<path> paths, FileMonitor1& fileSink)
{
	vector<future<void>> futures;
	for (auto& path : paths)
	{
		cout << path << endl;
		futures.emplace_back(async(listDir, path.string(), ref(fileSink)));
	}
	while(!fileSink.isDone())
	{
		if (fileSink.hasData())
		{
			string name = fileSink.pop_back();
			cout << name << endl;
		}
	}
	for (auto& fut : futures)
	{
		fut.wait();
	}

}

//void main()
//{
//	vector<path> paths;
//	for (directory_iterator it("c:\\"); it != directory_iterator(); ++it)
//	{
//		if (is_directory(it->status()))
//			paths.push_back(it->path());
//	}
//	FileMonitor1 fileSink;
//	listDirs(paths, fileSink);
//}

#endif // !_SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING