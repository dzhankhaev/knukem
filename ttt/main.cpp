#include <chrono>
#include <iostream>
#include <mutex>

using namespace std;
using namespace std::chrono;

// class LockRes
// {
// 	private:
// 		steady_clock::time_point start;
// 	public:
// 		LockRes()
// 			: start(steady_clock::now())
// 		{

// 		};
// 		~LockRes()
// 		{
// 			auto finish = steady_clock::now();
// 			auto dur = finish - start;
// 			cerr << duration_cast<milliseconds>(dur).count() << "ms" << endl;
// 		}
// };

void	catchRes()
{
	cerr << "start" << endl;
}

void	releaseRes()
{
	cerr << "end" << endl;
}

class LockRes
{
	std::mutex m;
	public:
		LockRes()
		{
			m.lock();
			catchRes();
		};
		~LockRes()
		{
			releaseRes();
			m.unlock();
		}
};

int main(int argc, char const *argv[])
{
	LockRes mmm;
	for (auto i = 0;i < 10000000;i++);
	cerr << "hobaa" << endl;
	for (auto i = 0;i < 30000000;i++);
	return 0;
}
