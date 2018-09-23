#include "reader.h"

void reader::start(std::condition_variable& cv, std::mutex& r_mutex, std::mutex& w_mutex, std::mutex& c_mutex, std::string file_name, int id)
{
	thread_ = std::thread(&reader::reader_function, std::ref(cv), std::ref(r_mutex), std::ref(w_mutex),  
		std::ref(c_mutex), file_name, id);
	thread_.detach();

}

void reader::reader_function(std::condition_variable& cv, std::mutex& r_mutex, std::mutex& w_mutex, std::mutex& c_mutex, std::string file_name, int id)
{

	w_mutex.lock();
	c_mutex.lock();
	readers_count_++;
	if (readers_count_ - 1 == 0)
		std::unique_lock<std::mutex> lock(r_mutex);
	else
		std::unique_lock<std::mutex> lock(r_mutex, std::try_to_lock);
	c_mutex.unlock();
	w_mutex.unlock();

	for (auto i = 0; i <= 5; i++)
		std::cout << "reader " << id << "\n";

	c_mutex.lock();
	readers_count_--;
	if (readers_count_ == 0) {
		cv.notify_all();
	}
	c_mutex.unlock();
}
