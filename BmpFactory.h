#ifndef _BMPFACTORY_H
#define _BMPFACTORY_H
// 2017.08.13 23:10

#include "FileFactory.h"
#include "BmpCommon.h"

class BmpFactory: public FileFactory {
public:
	BmpFactory();
	virtual size_t GetFile(std::shared_ptr<char[]>&) override;
	//virtual size_t GetFile(const std::string, const std::ios_base::openmode) override;
	virtual size_t GetFile(const std::string) override;
	unsigned char GetBitPerPxl() const;
	unsigned char GetOffBits() const;
	void SetBitPerPxl(const size_t);
	void SetResolution(const size_t, const size_t);
private:
	BmpFileHeader bmpFileHdr;
	BmpInfoHeader bmpInfoHdr;

	void UpdateBmpHeader();
};

#endif // _BMPFACTORY_H

