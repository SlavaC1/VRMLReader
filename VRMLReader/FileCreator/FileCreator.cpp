#include "FileCreator.h"
#include <boost\filesystem.hpp>

CFileCreator::CFileCreator(const std::string &Path, int SizeInMB) 
{
	boost::filesystem::path p(Path);

	if (! exists(p))
	{
		boost::filesystem::create_directories(p.branch_path());

		std::ofstream file(Path);

		const int size = 1024 * 500;
		char buffer[size];

		std::fill(buffer, buffer + sizeof(buffer), '1');

		int MegaBytes = (SizeInMB < 1) ? 2 : SizeInMB * 2;
		for (int i = 0; i < MegaBytes; i++)
			file.write(buffer, size);			

		file.close();
	}
}