#include <boost\chrono.hpp>
#include "FileReader.h"
#include "VRMLParser.h"

int main(int argc, char* argv[])
{
	try
	{
		namespace ch = boost::chrono;

		auto start = ch::high_resolution_clock::now();
		CFileReader fileReader(std::string("C:\\GIT\\VRMLReader\\wolf.wrl"));		

		const char*  data = fileReader.GetData();
		const size_t size = fileReader.GetFileSize();

		CVRMLParser par;
		par.Parse(data);

		auto end = ch::high_resolution_clock::now();
		auto duration = ch::duration_cast<boost::chrono::milliseconds>(end - start).count();

		std::cout << "Overall time: " << duration << " msec" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}