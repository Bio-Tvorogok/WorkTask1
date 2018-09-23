#pragma once
#include "base_thread.h"

class reader : public base_thread
{
private:
	std::thread thread_;
public:
	explicit reader() = default;
	~reader() = default;

	void start(std::condition_variable& cv, std::mutex& r_mutex, std::mutex& w_mutex, 
		std::mutex& c_mutex, std::string file_name, int id) override;
	static void reader_function(std::condition_variable& cv, std::mutex& r_mutex, 
		std::mutex& w_mutex, std::mutex& c_mutex, std::string file_name, int id);
};

