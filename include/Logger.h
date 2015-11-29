#pragma once

#ifndef _SPLAY_LOGGER_H_
#define _SPLAY_LOGGER_H_

#include "Common.h"

#include <spdlog/spdlog.h>

namespace splay
{

class Logger
{
public:
	//! Destructor.
	~Logger() = default;

	//! Copy constructor.
	Logger(const Logger&) = delete;
	//! Move constructor.
	Logger(Logger&&) NOEXCEPT = delete;
	//! Copy assign operator.
	Logger& operator=(const Logger&) = delete;
	//! Move assign operator.
	Logger& operator=(Logger&&) NOEXCEPT = delete;

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

} // namespace splay

#define SPLAY_LOG_CRITICAL(...) splay::Logger::Instance().force_log( \
	spdlog::level::critical, __VA_ARGS__)

#define SPLAY_LOG_DEBUG(...)    splay::Logger::Instance().force_log( \
	spdlog::level::debug, __VA_ARGS__)

#define SPLAY_LOG_ERROR(...)    splay::Logger::Instance().force_log( \
	spdlog::level::err, __VA_ARGS__)

#define SPLAY_LOG_INFO(...)     splay::Logger::Instance().force_log( \
	spdlog::level::info, __VA_ARGS__)

#define SPLAY_LOG_TRACE(...)    splay::Logger::Instance().force_log( \
	spdlog::level::trace, __VA_ARGS__)

#define SPLAY_LOG_WARNING(...)  splay::Logger::Instance().force_log( \
	spdlog::level::warn, __VA_ARGS__)

#endif // _SPLAY_LOGGER_H_
