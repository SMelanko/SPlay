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
}

spdlog::logger& Logger::Instance()
{
	std::call_once(mOnceFlag, [] {
		mInstance.reset(new Logger{});
	});

	assert(mInstance->mLogger != nullptr);

	return *(mInstance->mLogger.get());
}

} } // splay::log
