#include <iostream>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include "writer.h"
#include "reader.h"

#define R_COUNT 5
#define W_COUNT 5
#define REPEAT 1
#define DELAY 10

int readers = 0;
std::condition_variable cond;
std::mutex writers_access, readers_access, counter_access;
std::string file_name("file.txt");
std::vector<base_thread*> thread_vec;

int base_thread::readers_count_ = 0;
int main() {
	auto r_rand = R_COUNT;
	auto w_rand = W_COUNT;
	srand(time(nullptr));
	for (auto i = 0; i < R_COUNT + W_COUNT; i++)
	{
		const auto thread_rand = rand() % (r_rand + w_rand);
		if (thread_rand < r_rand) {
			thread_vec.push_back(new reader());
			if (r_rand) r_rand--;
		} else
		{
			thread_vec.push_back(new writer());
			if (w_rand) w_rand--;
		}
	}

	for (auto i = 0; i < R_COUNT + R_COUNT; i++)
		thread_vec[i]->start(std::ref(cond), std::ref(readers_access), std::ref(writers_access), 
			std::ref(counter_access), file_name, i);
	system("pause");
}
