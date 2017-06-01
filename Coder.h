#ifndef _CODER_H
#define _CODER_H

class Coder {
public:
	virtual std::string Encode(std::string&) const = 0;
	virtual std::string Decode(std::string&) const = 0;
};

#endif // _CODER_H
