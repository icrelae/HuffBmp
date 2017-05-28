#ifndef _CODERINFOIO_H
#define _CODERINFOIO_H

#include <iostream>
#include "Coder.h"

class CoderInfoIO {
public:
	virtual ~CoderInfoIO() { };

	virtual std::istream& ReadInfo(std::istream&) = 0;
	virtual std::ostream& WriteInfo(std::ostream&) = 0;
	virtual std::istream& Preprocess(std::istream &is) {
		return is;
	}
private:
	Coder *coderPtr;
};

#endif // _CODERINFOIO_H
