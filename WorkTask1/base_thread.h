#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class base_thread
{
protected:
	static int readers_count_;
public:
	virtual ~base_thread() = default;
	virtual void start(std::condition_variable& cv, std::mutex& r_mutex, 
		std::mutex& w_mutex, std::mutex& c_mutex, std::string file_name, int id) = 0;
};

