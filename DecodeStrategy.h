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
	size_t readBlockSize;
	size_t writeBlockSize;
};

#endif // _DECODESTRATEGY_H

