#pragma once

#include <boost/lexical_cast.hpp> 
namespace SimpleUtil
{
	bool SToI(const std::string val, int& out)
	{
		try {
			out = boost::lexical_cast<int>(val);
			return true;
		}
		catch (boost::bad_lexical_cast& e) {
			return false;
		}
	}
	bool IToS(int val,std::string& out)
	{
		try {
			out = boost::lexical_cast<std::string>(val);
			return true;;
		}
		catch (boost::bad_lexical_cast& e) {
			return false;
		}
	}
};
