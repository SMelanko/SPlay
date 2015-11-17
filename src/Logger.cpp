#include "Logger.h"

namespace splay
{
namespace log
{

std::unique_ptr<Logger> Logger::mInstance;
std::once_flag Logger::mOnceFlag;

Logger::Logger()
	: mLogger{ spdlog::rotating_logger_mt("file_logger", "splay_log", 1048576, 1) }
{
	// Creates a file rotating logger with 1 mb size max and 1 rotated file.
	mLogger->set_level(spdlog::level::debug);
}

Logger& Logger::Instance()
{
	std::call_once(mOnceFlag, [] {
		mInstance.reset(new Logger);
	});

	return *mInstance.get();
}

} } // splay::log
