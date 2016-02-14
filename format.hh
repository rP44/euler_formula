#pragma once
#ifndef FORMAT_HH
#define FORMAT_HH

#include <string>           //string
#include <boost/format.hpp> //format

template< typename First, typename... Args >
std::string format( const std::string& formatString,
                    First&& firstArg, Args&&... arg )
{
  boost::format formatter{ formatString };
  boost::format* list[] = { &( formatter % firstArg ), &( formatter % arg )... };
  ( void )list;
  return formatter.str();
}

inline const std::string& format( const std::string& string )
{
  return string;
}

inline std::string format()
{
  BOOST_ASSERT_MSG( false, "Format may not be used without arguments" );
  return {};
}

#endif
