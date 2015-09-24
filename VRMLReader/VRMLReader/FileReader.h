#pragma once

#include <string>
#include <exception>

class EFileReader : public std::exception
{
private:
public:
	EFileReader(const std::string &Error);
};

class CFileReader
{
private:
public:
	CFileReader(const std::string &Path);
};
