#include <iostream>
#include "cppformat/format.h"
#include "spdlog/spdlog.h"

int main()
{
	std::string str{ fmt::format("Hello {}!\n", "Slava") };
	fmt::print(str);

	//Create console, multithreaded logger
	auto console = spdlog::stdout_logger_mt("console");

	//
	// Create a daily logger - a new file is created every day on 2:30am
	//
	auto daily_logger = spdlog::daily_logger_mt("daily_logger", "daily", 23, 51);

	//
	// Create a file rotating logger with 5mb size max and 3 rotated files
	//
	auto log = spdlog::rotating_logger_mt("file_logger", "mylogfile", 10240, 3);
	for (int i = 200; i < 300; ++i)
		daily_logger->info("{} * {} equals {:>10}", i, i, i*i);

	spdlog::drop_all();

	return 0;
}
