#ifndef _CODER_H
#define _CODER_H

class Coder {
	public:
		virtual std::string Encode(char) = 0;
		virtual char Decode(std::string) = 0;
};

#endif // _CODER_H
