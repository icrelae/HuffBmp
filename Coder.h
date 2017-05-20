#ifndef _CODER_H
#define _CODER_H

class Coder {
public:
	virtual std::string Encode(std::string&) = 0;
	virtual std::string Decode(std::string&) = 0;
};

#endif // _CODER_H
