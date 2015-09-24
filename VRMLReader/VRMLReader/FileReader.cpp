#include "FileReader.h"
#include <boost/iostreams/device/mapped_file.hpp> 

EFileReader::EFileReader(const std::string &Error) 
{

}

CFileReader::CFileReader(const std::string &Path)
{
	boost::iostreams::mapped_file file;

	file.open(Path);

	if(file.is_open())
	{
		char *data = file.data();
		file.close();
	}
	else
	{
		throw EFileReader("Can't open file");

	}
	
}