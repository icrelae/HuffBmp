#ifndef _XORCODERINFOIO_H
#define _XORCODERINFOIO_H

#include "CoderInfoIO.h"
#include "XorCoder.h"

class XorCoderInfoIO: public CoderInfoIO {
public:
	XorCoderInfoIO(int i = 0);
	~XorCoderInfoIO();

	virtual std::istream& ReadInfo(std::istream&) override;
	virtual std::ostream& WriteInfo(std::ostream&) override;
	virtual std::istream& Read(std::istream&, char*, size_t) override;
	virtual std::ostream& Write(std::ostream&, char*, size_t) override;
	virtual size_t Gcount() const override;
	virtual const Coder* GetCoder() const override;
	int SetMgcNmb(int);
	int GetMgcNmb();
private:
	int mgcNmb;
	size_t gcount;
	XorCoder *coderPtr;
};

#endif // _XORCODERINFOIO_H
