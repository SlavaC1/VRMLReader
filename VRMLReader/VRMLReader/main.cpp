#include <boost\chrono.hpp>
#include "FileReader.h"
#include "VRMLParser.h"

int main(int argc, char* argv[])
{
	try
	{
		namespace ch = boost::chrono;

		auto start = ch::high_resolution_clock::now();
		CFileReader fileReader(std::string("C:\\GIT\\VRMLReader\\1.wrl"));
		auto end = ch::high_resolution_clock::now();

		auto duration = ch::duration_cast<boost::chrono::milliseconds>(end - start).count();

		const char*  data = fileReader.GetData();
		const size_t size = fileReader.GetFileSize();

		CVRMLParser par;
		par.Parse(data);

		int i = 7;
	}
	catch (EFileReader &e)
	{
		std::string err = e.what();
	}

	return 0;
}