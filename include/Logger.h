#pragma once

#ifndef _SPLAY_LOGGER_H_
#define _SPLAY_LOGGER_H_

#include <memory>

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
	static Logger& Instance();

	spdlog::details::line_logger Debug()
	{
		if (mLogger->level() != spdlog::level::debug)
			mLogger->set_level(spdlog::level::debug);
		return Instance().Ref().debug();
	}

private:
	//! Constructor.
	Logger();

	spdlog::logger& Ref()
	{
		return *mLogger.get();
	}

private:
	//! Logger instance.
	static std::unique_ptr<Logger> mInstance;
	//! Helper flag for creation logger only once.
	static std::once_flag mOnceFlag;
	//! File logger.
	std::shared_ptr<spdlog::logger> mLogger;
};

} } // splay::log

//#define LOG_TRACE splay::log::GetLogger(spdlog::level::trace)
#define SPLAY_LOG_DEBUG splay::log::Logger::Instance().Debug()
//#define LOG_NOTICE
//#define LOG_WARN
//#define LOG_ERROR
//#define LOG_CRITICAL
//#define LOG_ALERT
//#define LOG_EMERG

#endif // _SPLAY_LOGGER_H_
