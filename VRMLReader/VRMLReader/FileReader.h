#pragma once

#include "Exception.h"
#include <boost/iostreams/device/mapped_file.hpp> 

// Exception class for CFileReader
class EFileReader : public EBasicException
{
public:
	EFileReader(const char* Msg) : EBasicException(Msg){}
	EFileReader(const std::string &Msg) : EBasicException(Msg){}
};

// Class to map large files into memory
class CFileReader
{
private:
	boost::iostreams::mapped_file_source m_File;
	const char* m_Data;
	size_t      m_FileSize;

public:
	CFileReader(const std::string &Path);
	~CFileReader();
	const char*  GetData() const;
	const size_t GetFileSize() const;
};
