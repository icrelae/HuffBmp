#ifndef _CODERINFOIO_H
#define _CODERINFOIO_H

#include <iostream>
#include "Coder.h"

enum PreprcsRslt {
	RSLTOK,
	RSLTERROR,
};

class CoderInfoIO {
public:
	virtual std::istream& ReadInfo(std::istream&) = 0;
	virtual std::ostream& WriteInfo(std::ostream&) = 0;
	virtual std::istream& read(char*, size_t) = 0;
	virtual std::ostream& write(char*, size_t) = 0;
	virtual enum PreprcsRslt Preprocess(std::istream&, std::istream&) {
		return RSLTOK;
	}
	virtual const Coder* GetCoder() const = 0;
};

#endif // _CODERINFOIO_H
