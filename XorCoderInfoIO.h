#ifndef _XORCODERINFOIO_H
#define _XORCODERINFOIO_H

#include <iostream>
#include "CoderInfoIO.h"
#include "XorCoder.h"

class XorCoderInfoIO: public CoderInfoIO {
public:
	XorCoderInfoIO(int i = 0);

	virtual std::istream& ReadInfo(std::istream&) override;
	virtual std::ostream& WriteInfo(std::ostream&) override;
	void SetMgcNmb(int);
	int GetMgcNmb();
private:
	int mgcNmb;
};

#endif // _XORCODERINFOIO_H
