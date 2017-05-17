#include <string>
#include <random>
#include <ctime>
#include <bitset>
#include "XorCoder.h"

namespace {
	// using 'static global variable' to avoid construct 'randomEngine' for
	// every 'XorCoder' objects
	std::default_random_engine randomEngine(time(0));
	std::uniform_int_distribution<char> distChar;
}

// passing 'mgcNmb' in when decode, leave it empty when encode
XorCoder::XorCoder(int mgcNmb): vecMgcNmbIndex(0)
{
	int i = 0;
	char *mgcNmbPtr = reinterpret_cast<char*>(&mgcNmb);
	while (i++ < 4) {
		while (*mgcNmbPtr == 0)
			*mgcNmbPtr = distChar(randomEngine);
		vecMgcNmb.push_back(*mgcNmbPtr++);
	}
}

XorCoder::~XorCoder()
{
}

std::string XorCoder::Encode(std::string &originCode)
{
	std::string result = "";
	
	while (originCode.size() > 7) {
		// bit code to 'char'
		std::bitset<8> oneByte =
			std::bitset<8>(originCode, 0, 8, CODE_ZERO, CODE_ONE);
		char code = static_cast<unsigned char>(oneByte.to_ulong());
		// index determained by plaintext so we don't change 'code' here
		// as opposed to 'Decode'
		result += code ^ vecMgcNmb[vecMgcNmbIndex];
		vecMgcNmbIndex = (code >> 2) % 4;
		originCode = originCode.erase(0, 8);
	}
	return result;
}

std::string XorCoder::Decode(std::string &originCode)
{
	std::string result = "";
	
	while (originCode.size() > 7) {
		// bit code to 'char'
		std::bitset<8> oneByte =
			std::bitset<8>(originCode, 0, 8, CODE_ZERO, CODE_ONE);
		char code = static_cast<unsigned char>(oneByte.to_ulong());
		// index determained by plaintext so we change the 'code' here
		// as opposed to 'Encode'
		code ^= vecMgcNmb[vecMgcNmbIndex];
		result += code;
		vecMgcNmbIndex = (code >> 2) % 4;
		originCode = originCode.erase(0, 8);
	}
	return result;
}

void XorCoder::ResetVecMgcNmbIndex(size_t i)
{
	vecMgcNmbIndex = i;
}

int XorCoder::GetMgcNmb()
{
	int result, i = 0;
	char *cPtr = reinterpret_cast<char*>(&result);
	while (i < 4)
		*cPtr++ = vecMgcNmb[i++];
	return result;
}
