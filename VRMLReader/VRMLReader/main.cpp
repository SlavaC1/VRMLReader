#include "FileReader.h"
#include <boost\chrono.hpp>

int main(int argc, char* argv[])
{
	try
	{
		auto start = boost::chrono::high_resolution_clock::now();
		CFileReader fileReader(std::string("c:\\test\\1.txt"));
		auto end = boost::chrono::high_resolution_clock::now();

		auto duration = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();

		int i = 7;
	}
	catch (EFileReader &e)
	{
		e.what();
	}

	return 0;
}