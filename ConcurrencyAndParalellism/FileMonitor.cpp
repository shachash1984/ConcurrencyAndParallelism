#ifndef _SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING
#define _SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING

#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <future>

using namespace std::tr2::sys;
using namespace std;

class FileMonitor
{
public:
	void push_back(string file)
	{
		lock_guard<mutex> lck(_mtx);
		_allFiles.push_back(move(file));
	}
	void print()
	{
		lock_guard<mutex> lck(_mtx);
		for (auto& name : _allFiles)
			cout << name << endl;
	}
private:
	vector<string> _allFiles;
	mutex _mtx;
};

void listDir(string path, FileMonitor& fileSink)
{
	for (directory_iterator it(path); it != directory_iterator(); ++it)
	{
		if (is_regular_file(it->status()))
		{
			fileSink.push_back(it->path().string());
		}
	}
}

void listDirs(vector<path> paths, FileMonitor& fileSink)
{
	vector<future<void>> futures;
	for (auto& path : paths)
	{
		cout << path << endl;
		futures.emplace_back(async(listDir, path.string(), ref(fileSink)));
	}
	for (auto& fut : futures)
	{
		fut.wait();
	}

}

//int main()
//{
//	vector<path> paths;
//	for (directory_iterator it("c:\\"); it != directory_iterator(); ++it)
//	{
//		if (is_directory(it->status()))
//			paths.push_back(it->path());
//	}
//
//	FileMonitor fileSink;
//	listDirs(paths, fileSink);
//	fileSink.print();
//
//	return 0;
//}

#endif // !_SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING