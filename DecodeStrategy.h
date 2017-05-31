#ifndef _DECODESTRATEGY_H
#define _DECODESTRATEGY_H
// 2017.05.31 19:24

#include "CoderInfoIO.h"

class DecodeStrategy {
public:
	DecodeStrategy(CoderInfoIO *p = nullptr);
	void SetCoderInfoPtr(CoderInfoIO*);
	int Decode(const std::string&, const std::string&);
private:
	CoderInfoIO *coderInfoPtr;
	static const size_t readBlockSize = 64;
	static const size_t writeBlockSize = readBlockSize * 5;
};

#endif // _DECODESTRATEGY_H

