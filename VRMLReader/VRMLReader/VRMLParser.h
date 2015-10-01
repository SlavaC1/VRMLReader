#pragma once

#include "Exception.h"

// Exception class for CVRMLParser
class EVRMLParser : public EBasicException
{
public:
	EVRMLParser(const char* Msg) : EBasicException(Msg){}
	EVRMLParser(const std::string &Msg) : EBasicException(Msg){}
};

class CVRMLParser
{
private:
public:
	CVRMLParser();
	virtual ~CVRMLParser();
	void Parse(const std::string &Data);
};