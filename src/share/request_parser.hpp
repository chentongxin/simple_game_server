//
// request_parser.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REQUEST_PARSER_HPP
#define HTTP_REQUEST_PARSER_HPP

#include <tuple>
#include <string>
#include <boost/lexical_cast.hpp>
#include "request.hpp"

namespace server {

struct request;

/// Parser for incoming requests.
class request_parser
{
public:
  /// Construct ready to parse the request method.
  request_parser();

  /// Reset to initial parser state.
  void reset();

  /// Result of parse.
  enum result_type { good, bad, indeterminate };

  template <typename InputIterator>
  void parse_content(request& req, InputIterator begin, InputIterator end)
  {
	  size_t content_length = 0;
	  for (std::size_t i = 0; i < req.headers.size(); ++i)
	  {
		  if (headers_equal(req.headers[i].name, "Content-Length"))
		  {
			  try
			  {
				  content_length = boost::lexical_cast<std::size_t>(req.headers[i].value);
				  break;
			  }
			  catch (boost::bad_lexical_cast&)
			  {
				  content_length = 0;
			  }
		  }
	  }
	  if (content_length > 0 && (begin + content_length) <= end)
	  {
		  req.content = std::string(begin, begin + content_length);
	  }
  }

  /// Parse some data. The enum return value is good when a complete request has
  /// been parsed, bad if the data is invalid, indeterminate when more data is
  /// required. The InputIterator return value indicates how much of the input
  /// has been consumed.
  template <typename InputIterator>
  std::tuple<result_type, InputIterator> parse(request& req,
      InputIterator begin, InputIterator end)
  {
    while (begin != end)
    {
      result_type result = consume(req, *begin++);
	  if (result == good || result == bad)
	  {
		  if (result == good && begin != end)
		  {
			  parse_content(req, begin, end);
		  }
		  return std::make_tuple(result, begin);
	  }
    }
    return std::make_tuple(indeterminate, begin);
  }

  
private:

  /// Handle the next character of input.
  result_type consume(request& req, char input);

  /// Check if a byte is an HTTP character.
  static bool is_char(int c);

  /// Check if a byte is an HTTP control character.
  static bool is_ctl(int c);

  /// Check if a byte is defined as an HTTP tspecial character.
  static bool is_tspecial(int c);

  /// Check if a byte is a digit.
  static bool is_digit(int c);

  /// Check if two characters are equal, without regard to case.
  static bool tolower_compare(char a, char b);
  /// Check whether the two request header names match.
  bool headers_equal(const std::string& a, const std::string& b);

  /// The current state of the parser.
  enum state
  {
    method_start,
    method,
    uri,
    http_version_h,
    http_version_t_1,
    http_version_t_2,
    http_version_p,
    http_version_slash,
    http_version_major_start,
    http_version_major,
    http_version_minor_start,
    http_version_minor,
    expecting_newline_1,
    header_line_start,
    header_lws,
    header_name,
    space_before_header_value,
    header_value,
    expecting_newline_2,
    expecting_newline_3
  } state_;
};

} // namespace server

#endif // HTTP_REQUEST_PARSER_HPP
