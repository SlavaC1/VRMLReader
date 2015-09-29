#include "Exception.h"

EBasicException::EBasicException(const char* Msg) : m_Msg(Msg)
{}

EBasicException::EBasicException(const std::string &Msg) : m_Msg(Msg)
{}

const char* EBasicException::what() const throw()
{
	return m_Msg.c_str();
}