#include <fstream>
#include <memory>
#include <bitset>
#include "DecodeStrategy.h"

DecodeStrategy::DecodeStrategy(CoderInfoIO *p): coderInfoPtr(p)
{
}

void DecodeStrategy::SetCoderInfoPtr(CoderInfoIO *p)
{
	coderInfoPtr = p;
}

int DecodeStrategy::Decode(const std::string &iFile, const std::string &oFile)
{
	std::ifstream ifs(iFile, std::fstream::binary);
	std::ofstream ofs(oFile, std::fstream::binary);
	if (!ifs || !ofs)
		throw std::runtime_error("cannot open file!");
	coderInfoPtr->ReadInfo(ifs);

	const Coder *coderPtr = coderInfoPtr->GetCoder();
	size_t gcount = readBlockSize, writeBufferIndex;
	std::shared_ptr<char> readBufferSp(new char[readBlockSize]);
	std::shared_ptr<char> writeBufferSp(new char[writeBlockSize]);
	char *readBuffer = readBufferSp.get();
	char *writeBuffer = writeBufferSp.get();
	std::string originCode, plainCode;
	while (gcount == readBlockSize) {
		ifs.read(readBuffer, readBlockSize);
		gcount = ifs.gcount();
		for (size_t i = 0; i < gcount; ++i)
			originCode += std::bitset<8>(readBuffer[i]).to_string();
		plainCode = coderPtr->Decode(originCode);
		writeBufferIndex = 0;
		while (plainCode.size() > 7) {
			std::bitset<8> oneByte = std::bitset<8>(plainCode, 0, 8);
			const char c = static_cast<char>(oneByte.to_ulong());
			writeBuffer[writeBufferIndex++] = c;
			plainCode.erase(0, 8);
		}
		ofs.write(writeBuffer, writeBufferIndex);
	}
	if (originCode.size() !=  0)
		throw std::runtime_error("decode error(originCode != 0)!");

	return 0;
}
