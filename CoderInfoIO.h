#ifndef _CODERINFOIO_H
#define _CODERINFOIO_H

#include <iostream>

class CoderInfoIO {
public:
	virtual std::istream& ReadInfo(std::istream&) = 0;
	virtual std::ostream& WriteInfo(std::ostream&) = 0;
};

#endif // _CODERINFOIO_H
