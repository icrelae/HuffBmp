#ifndef _HUFFMANCODER_H
#define _HUFFMANCODER_H

#include <map>
#include "coder.h"

class HuffmanCoder: public Coder {
	public:
		HuffmanCoder(map<char, std::string> map);
		virtual ~HuffmanCoder();
		virtual std::string Encode(char);
		virtual char Decode(std::string);
		unsigned AddWeight(char, unsigned w = 1);
	private:
		map<char, std::string> mapTable;
};

#endif // _HUFFMANCODER_H
