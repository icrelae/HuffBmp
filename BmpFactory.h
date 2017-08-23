#ifndef _BMPFACTORY_H
#define _BMPFACTORY_H
// 2017.08.13 23:10

#include "FileFactory.h"
#include "BmpCommon.h"

class BmpFactory: public FileFactory {
public:
	BmpFactory();
	virtual bool GetFile(const std::string, const std::ios_base::openmode) override;
	void SetBitPerPxl(const int);
	void SetResolution(const int, const int);
private:
	BmpFileHeader bmpFileHdr;
	BmpInfoHeader bmpInfoHdr;

	void UpdateBmpHeader();
};

#endif // _BMPFACTORY_H

