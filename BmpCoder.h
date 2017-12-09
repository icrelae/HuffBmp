#ifndef _BMPCODER_H
#define _BMPCODER_H
// 2017.12.02 18:58

#include <cstddef>
#include <memory>
#include "BmpCommon.h"

class BmpCoder {
public:
	static const size_t WIDTHDFT = 1920;
	static const size_t HEIGHTDFT = 1080;
	static const size_t MAXLENGTH = 19200 * 10800;
	static bool IsValidBmp(const BmpFileHeader&, const BmpInfoHeader&);

	BmpCoder(char m = 3);
	void SetMask(char);
	int Decode(std::shared_ptr<const char[]>, std::ofstream&);
	unsigned Encode(std::ifstream&, std::shared_ptr<char[]>&);
private:
	char mask;
	static const size_t BUFFSIZE = 1024;
	int GetPlain(const char*, size_t, std::ofstream&);
	int GetCipher(std::ifstream&, size_t, char*, size_t);
};

#endif // _BMPCODER_H
