#pragma once

#ifndef _SPLAY_LOGGER_H_
#define _SPLAY_LOGGER_H_

#include <memory>

#include "spdlog\spdlog.h"

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

	static Logger& GetInstance();

	std::shared_ptr<spdlog::logger> Ref()
	{
		return mLogger;
	}

private:
	//! Constructor.
	Logger();

private:
	//! File logger instance.
	std::shared_ptr<spdlog::logger> mLogger;

	static std::unique_ptr<Logger> mInstance;
	static std::once_flag mOnceFlag;
};

} } // splay::log

//#define LOG_TRACE splay::log::GetLogger(spdlog::level::trace)
#define LOG_DEBUG splay::log::Logger::GetInstance().Ref()->debug()
//#define LOG_NOTICE
//#define LOG_WARN
//#define LOG_ERROR
//#define LOG_CRITICAL
//#define LOG_ALERT
//#define LOG_EMERG

#endif // _SPLAY_LOGGER_H_
