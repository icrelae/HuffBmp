#ifndef _BMPFACTORY_H
#define _BMPFACTORY_H
// 2017.08.13 23:10

#include "FileFactory.h"
#include "BmpCommon.h"

class BmpFactory: public FileFactory {
public:
	BmpFileHeader bmpFileHdr;
	BmpInfoHeader bmpInfoHdr;

	BmpFactory();
	virtual std::fstream GetFile(string, int) override;
};

#endif // _BMPFACTORY_H

