#ifndef _ENCODESTRATEGY_H
#define _ENCODESTRATEGY_H
// 2017.05.30 15:33

#include "CoderInfoIO.h"

class EncodeStrategy {
public:
	EncodeStrategy(CoderInfoIO *p = nullptr);
	void SetCoderInfoPtr(CoderInfoIO*);
	int Encode(const std::string&, const std::string&);
private:
	CoderInfoIO *coderInfoPtr;
	static const size_t readBlockSize = 64;
	static const size_t writeBlockSize = readBlockSize * 5;
};

#endif // _ENCODESTRATEGY_H

