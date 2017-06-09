#ifndef _BMPCODERINFOIO_H
#define _BMPCODERINFOIO_H
// 2017.06.09 21:22

#include "CoderInfoIO.h"
#include "BmpCoder.h"

class BmpCoderInfoIO {
public:
	void ReadBmpFileHeader(std::istream&);
	void ReadBmpInfoHeader(std::istream&);
	BmpFileHeader bmpFileHdr;
	BmpInfoHeader bmpInfoHdr;
};

#endif // _BMPCODERINFOIO_H

