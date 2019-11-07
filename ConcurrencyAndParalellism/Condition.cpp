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

class FileMonitor2
{
public:
	void push_back(string file)
	{
		lock_guard<mutex> lck(_mtx);
		_allFiles.push_back(move(file));
		_cond.notify_one();
	}
	string pop_back()
	{
		unique_lock<mutex> lck(_mtx);
		_cond.wait(lck, [this] {return !_allFiles.empty(); });
		string name = move(_allFiles.back());
		_allFiles.pop_back();
		return name;
	}
private:
	vector<string> _allFiles;
	mutable mutex _mtx;
	mutable condition_variable _cond;
};

void listDir(string path, FileMonitor2& fileSink)
{
	for (directory_iterator it(path); it != directory_iterator(); ++it)
	{
		if (is_regular_file(it->status()))
		{
			
			string name = it->path().string();
			fileSink.push_back(it->path().string());
		}
	}
}

void listDirs(vector<path> paths, FileMonitor2& fileSink)
{
	vector<future<void>> futures;
	for (auto& path : paths)
	{
		cout << path << endl;
		futures.emplace_back(async(listDir, path.string(), ref(fileSink)));
	}
	while (true)
	{
		string name = fileSink.pop_back();
		cout << name << endl;
	}
	for (auto& fut : futures)
	{
		fut.wait();
	}

}

void main()
{
	vector<path> paths;
	for (directory_iterator it("C:\\FileNameChangeTest"); it != directory_iterator(); ++it)
	{
		if (is_directory(it->status()))
			paths.push_back(it->path());
	}
	FileMonitor2 fileSink;
	listDirs(paths, fileSink);
}

#endif // !_SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING