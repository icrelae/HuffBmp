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
XorCoder::XorCoder(int mgcNmb): mgcNmbsIndex(0)
{
	SetMgcNmb(mgcNmb);
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
		result += code ^ mgcNmbs[mgcNmbsIndex];
		mgcNmbsIndex = (code >> 2) % 4;
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
		code ^= mgcNmbs[mgcNmbsIndex];
		result += code;
		mgcNmbsIndex = (code >> 2) % 4;
		originCode = originCode.erase(0, 8);
	}
	return result;
}

void XorCoder::ResetVecMgcNmbIndex(size_t i)
{
	mgcNmbsIndex = i;
}

int XorCoder::SetMgcNmb(int mgcNmb)
{
	int i = 0, mgcNmbNot0 = mgcNmb;
	char *mgcNmbPtr = reinterpret_cast<char*>(&mgcNmb);
	while (i++ < 4) {
		while (!mgcNmbNot0 && *mgcNmbPtr == 0)
			*mgcNmbPtr = distChar(randomEngine);
		mgcNmbs.push_back(*mgcNmbPtr++);
	}
	return mgcNmb;
}

int XorCoder::GetMgcNmb() const
{
	int result, i = 0;
	char *cPtr = reinterpret_cast<char*>(&result);
	while (i < 4)
		*cPtr++ = mgcNmbs[i++];
	return result;
}
