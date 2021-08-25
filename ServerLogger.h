#pragma once
#include <boost/log/trivial.hpp>
#include <boost/log/sources/global_logger_storage.hpp>

enum severity_level
{
    Debug,
    Error,
    Info,
    Warning
};

BOOST_LOG_GLOBAL_LOGGER(logger, boost::log::sources::severity_logger_mt< severity_level >)

// The formatting logic for the severity level
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
    std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
{
    static const char* const str[] =
    {
        "DEBUG",
        "ERROR",
        "INFO",
        "WARNING"
    };
    if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str)))
        strm << str[lvl];
    else
        strm << static_cast<int>(lvl);
    return strm;
}

