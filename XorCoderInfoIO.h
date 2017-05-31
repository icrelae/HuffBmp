#ifndef _XORCODERINFOIO_H
#define _XORCODERINFOIO_H

#include <iostream>
#include "CoderInfoIO.h"
#include "XorCoder.h"

class XorCoderInfoIO: public CoderInfoIO {
public:
	XorCoderInfoIO(int i = 0);
	~XorCoderInfoIO();

	virtual std::istream& ReadInfo(std::istream&) override;
	virtual std::ostream& WriteInfo(std::ostream&) override;
	virtual const Coder* GetCoder() const override;
	int SetMgcNmb(int);
	int GetMgcNmb();
private:
	int mgcNmb;
	XorCoder *coderPtr;
};

#endif // _XORCODERINFOIO_H
