#ifndef _FILEFACTORY_H
#define _FILEFACTORY_H
// 2017.08.13 22:10

#include <fstream>

class FileFactory {
public:
	virtual bool GetFile(const std::string fileName, const std::ios_base::openmode mode) = 0;
};

#endif // _FILEFACTORY_H

