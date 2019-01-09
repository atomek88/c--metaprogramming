#include<random>
#include<vector>
#include<string>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<chrono>
#include<cmath>
#include<iostream>
#include<sstream>
using namespace std;
using namespace std::chrono;

thread_local random_device rd;
thread_local default_random_engine engine{rd()};

int constexpr workers{10};
int workers_done_with_current_task{0};

mutex mtx;
condition_variable cv;

vector<string> tasks
= { "Digging Foundation", "Pouring Concrete", "Framing", "Roofing", "Drywalling", "Painting" };
auto current_task = tasks.begin();

void maybeMoveToNextTask() // Precondition: mtx is locked
{
	if (workers == workers_done_with_current_task) {
		cout << *current_task + " completed!\n\n";
		current_task++;
		workers_done_with_current_task = 0;
		cv.notify_all();
	}
}

void work()
{
	normal_distribution<> dist(10000, 1500);
	ostringstream oss;
	oss << this_thread::get_id();
	string myName = oss.str();

	for (auto my_current_task = tasks.begin();;) {
		if (my_current_task == tasks.end())
			return;
		this_thread::sleep_for(milliseconds(lround(dist(engine))));
		cout << "Worker "s + myName + " completed task "s + *my_current_task + "\n";
		my_current_task++;
		unique_lock<mutex> lck{mtx};
		workers_done_with_current_task++;
		maybeMoveToNextTask();
		cv.wait(lck, [&]() { return my_current_task == current_task; });
	}
}

int main()
{
	vector<thread> threads;
	for (int i = 0; i < workers; i++) {
		threads.push_back(thread{work});
	}
	for (auto &thr : threads)
		thr.join();
	return 0;
}