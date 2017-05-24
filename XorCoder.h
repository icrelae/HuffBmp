#ifndef _XORCODER_H
#define _XORCODER_H

#include <vector>
#include "Coder.h"

class XorCoder: public Coder {
public:
	XorCoder(int mgcNmb = 0);
	virtual ~XorCoder();

	virtual std::string Encode(std::string&) override;
	virtual std::string Decode(std::string&) override;
	void ResetVecMgcNmbIndex(size_t i = 0);
	int SetMgcNmb(int mgcNmb = 0);
	int GetMgcNmb() const;
private:
	static const char CODE_ZERO = '0';
	static const char CODE_ONE = '1';
	std::vector<char> mgcNmbs;
	size_t mgcNmbsIndex;
};

#endif // _XORCODER_H
