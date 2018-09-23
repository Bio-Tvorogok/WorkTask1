#include "writer.h"

void writer::start(std::condition_variable& cv, std::mutex& r_mutex, std::mutex& w_mutex, std::mutex& c_mutex, std::string file_name, int id)
{
	thread_ = std::thread(&writer::writer_function, std::ref(cv), std::ref(r_mutex), std::ref(w_mutex), 
		file_name, id);
	thread_.detach();
}

void writer::writer_function(std::condition_variable& cv, std::mutex& r_mutex, std::mutex& w_mutex, std::string file_name, int id)
{
	w_mutex.lock();
	std::unique_lock<std::mutex> lock(r_mutex);
	if (readers_count_ > 0)
		cv.wait(lock);
	w_mutex.unlock();

	for (auto i = 0; i <= 5; i++)
		std::cout << "writer " << id << "\n";

	lock.unlock();
}
