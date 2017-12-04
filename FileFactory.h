#ifndef _FILEFACTORY_H
#define _FILEFACTORY_H
// 2017.08.13 22:10

#include <fstream>
#include <memory>

class FileFactory {
public:
	virtual size_t GetFile(std::shared_ptr<char[]>&) = 0;
	//virtual size_t GetFile(const std::string fileName,
	//	const std::ios_base::openmode mode) = 0;
	virtual size_t GetFile(const std::string fileName) = 0;
};

#endif // _FILEFACTORY_H

