#pragma once

#include <exception>
#include <string>

//  Basic exception class
class EBasicException : public std::exception
{
protected:
	std::string m_Msg;
public:
	EBasicException(const char* Msg);
	EBasicException(const std::string &Msg);
	virtual ~EBasicException() throw (){}
	virtual const char* what() const throw();
};