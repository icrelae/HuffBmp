#ifndef _BMPCODER_H
#define _BMPCODER_H
// 2017.06.09 21:22

#include "Coder.h"
#include "BmpCommon.h"

class BmpCoder: public Coder {
public:
	virtual std::string Encode(std::string&) const override;
	virtual std::string Decode(std::string&) const override;
};

#endif // _BMPCODER_H
