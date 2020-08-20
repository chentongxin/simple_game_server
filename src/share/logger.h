#pragma once

#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/keyword.hpp>

#include <boost/log/attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_feature.hpp>  //
#include <boost/log/sinks.hpp>//
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>//
#include <boost/log/attributes/named_scope.hpp>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

enum SeverityLevel
{
	trace = 0,
	debug,
	info,
	warn,
	error,
	fatal
};

template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
	std::basic_ostream< CharT, TraitsT >& strm, SeverityLevel lvl)
{
	static const char* const str[] =
	{
		"TRACE",
		"DEBUG",
		"INFO",
		"WARN",
		"ERROR",
		"FATAL"
	};
	if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str)))
		strm << str[lvl];
	else
		strm << static_cast<int>(lvl);
	return strm;
}
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(vdsu_logger, src::severity_logger_mt<SeverityLevel>);

BOOST_LOG_ATTRIBUTE_KEYWORD(log_severity, "Severity", SeverityLevel)
BOOST_LOG_ATTRIBUTE_KEYWORD(log_timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(log_uptime, "Uptime", attrs::timer::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(log_scope, "Scope", attrs::named_scope::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(log_threadId, "ThreadID", attrs::current_thread_id::value_type)

typedef src::severity_logger_mt<SeverityLevel> vdsu_logger_mt;


void g_InitLog(SeverityLevel file_level, const std::string& fullpath, const std::string& name);
void g_SetLevel(int file_level);

static std::stringstream ss;

extern int g_log_level;

template<typename T>
void LogDebug( const T& t)
{
	if (g_log_level <= debug)
	{
		ss << t << std::endl;;
		vdsu_logger_mt& vlg = vdsu_logger::get();
		BOOST_LOG_SEV(vlg, debug) << ss.str();
	}
	ss.str("");
}

template<class T, class ...Args>
void LogDebug(T head, Args... args)
{
	ss << head;
	LogDebug(args...);
}

template<typename T>
void LogInfo(const T& t)
{
	if (g_log_level<=info)
	{
		ss << t << std::endl;;
		vdsu_logger_mt& vlg = vdsu_logger::get();
		BOOST_LOG_SEV(vlg, info) << ss.str();
	}
	ss.str("");
}

template<class T, class ...Args>
void LogInfo(T head, Args... args)
{
	ss << head;
	LogInfo(args...);
}

template<typename T>
void LogError(const T& t)
{
	if (g_log_level <= error)
	{
		ss << t << std::endl;;
		vdsu_logger_mt& vlg = vdsu_logger::get();
		BOOST_LOG_SEV(vlg, error) << ss.str();
	}
	ss.str("");
}

template<class T, class ...Args>
void LogError(T head, Args... args)
{
	ss << head;
	LogError(args...);
}


