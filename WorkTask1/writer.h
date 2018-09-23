#pragma once
#include "base_thread.h"

class writer : public base_thread
{
private:
	std::thread thread_;
public:
	explicit writer() = default;
	~writer() = default;

	void start(std::condition_variable& cv, std::mutex& r_mutex, std::mutex& w_mutex, 
		std::mutex& c_mutex, std::string file_name, int id) override;
	static void writer_function(std::condition_variable& cv, std::mutex& r_mutex, 
		std::mutex& w_mutex, std::string file_name, int id);
};

