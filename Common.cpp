#include "Common.h"

size_t CalcFileSize(std::istream &is)
{
	std::streampos pos = is.tellg();
	is.seekg(0, std::fstream::end);
	size_t fileSize = is.tellg();
	is.seekg(pos);
	return fileSize;
}
