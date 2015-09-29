#include "FileReader.h"

CFileReader::CFileReader(const std::string &Path) : m_Data(nullptr), m_FileSize(0)
{
	m_File.open(Path);

	if (m_File.is_open())	
		m_Data = m_File.data();	
	else	
		throw EFileReader("Can't open file");		
}

CFileReader::~CFileReader()
{
	if (m_File.is_open())
		m_File.close();
}

const char* CFileReader::GetData() const
{
	return m_Data;
}

const size_t CFileReader::GetFileSize() const
{
	return m_File.size();
}