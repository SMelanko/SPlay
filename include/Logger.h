#pragma once

#ifndef _SPLAY_LOGGER_H_
#define _SPLAY_LOGGER_H_

#include <spdlog/spdlog.h>

namespace splay
{
namespace log
{

class Logger
{
public:
	//! Destructor.
	~Logger() = default;

	//! Copy constructor.
	Logger(const Logger&) = delete;
	//! Move constructor.
	Logger(Logger&&) noexcept = delete;
	//! Copy assign operator.
	Logger& operator=(const Logger&) = delete;
	//! Move assign operator.
	Logger& operator=(Logger&&) noexcept = delete;

	//! Returns singleton instance of the logger.
	static spdlog::logger& Instance();

private:
	//! Constructor.
	Logger();

private:
	//! Logger instance.
	static std::unique_ptr<Logger> mInstance;
	//! Helper flag for the creating logger only once.
	static std::once_flag mOnceFlag;

	//! File logger.
	std::shared_ptr<spdlog::logger> mLogger;
};

} } // splay::log

#define SPLAY_LOG_ALERT(...)    splay::log::Logger::Instance().force_log(spdlog::level::alert, __VA_ARGS__)
#define SPLAY_LOG_CRITICAL(...) splay::log::Logger::Instance().force_log(spdlog::level::critical, __VA_ARGS__)
#define SPLAY_LOG_DEBUG(...)    splay::log::Logger::Instance().force_log(spdlog::level::debug, __VA_ARGS__)
#define SPLAY_LOG_EMERG(...)    splay::log::Logger::Instance().force_log(spdlog::level::emerg, __VA_ARGS__)
#define SPLAY_LOG_ERROR(...)    splay::log::Logger::Instance().force_log(spdlog::level::err, __VA_ARGS__)
#define SPLAY_LOG_INFO(...)     splay::log::Logger::Instance().force_log(spdlog::level::info, __VA_ARGS__)
#define SPLAY_LOG_NOTICE(...)   splay::log::Logger::Instance().force_log(spdlog::level::notice, __VA_ARGS__)
#define SPLAY_LOG_TRACE(...)    splay::log::Logger::Instance().force_log(spdlog::level::trace, __VA_ARGS__)
#define SPLAY_LOG_WARNING(...)  splay::log::Logger::Instance().force_log(spdlog::level::warn, __VA_ARGS__)

#endif // _SPLAY_LOGGER_H_
