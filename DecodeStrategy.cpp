#include <fstream>
#include <memory>
#include <bitset>
#include "DecodeStrategy.h"

DecodeStrategy::DecodeStrategy(CoderInfoIO *p): coderInfoPtr(p)
{
	readBlockSize = 64;
	writeBlockSize = readBlockSize * 8;
}

void DecodeStrategy::SetCoderInfoPtr(CoderInfoIO *p)
{
	coderInfoPtr = p;
}

int DecodeStrategy::Decode(const std::string &iFile, const std::string &oFile)
{
	size_t fileSize, writedSize = 0;
	std::ifstream ifs(iFile, std::fstream::binary);
	std::ofstream ofs(oFile, std::fstream::binary);
	if (!ifs || !ofs)
		throw std::runtime_error("cannot open file!");

	coderInfoPtr->Preprocess(ifs);
	coderInfoPtr->ReadInfo(ifs);
	fileSize = coderInfoPtr->GetFileSize();

	const Coder *coderPtr = coderInfoPtr->GetCoder();
	size_t gcount = readBlockSize, writeBufferIndex;
	std::shared_ptr<char> readBufferSp(new char[readBlockSize]);
	std::shared_ptr<char> writeBufferSp(new char[writeBlockSize]);
	char *readBuffer = readBufferSp.get();
	char *writeBuffer = writeBufferSp.get();
	std::string originCode, plainCode;
	while (gcount == readBlockSize) {
		coderInfoPtr->Read(ifs, readBuffer, readBlockSize);
		if (!(gcount = coderInfoPtr->Gcount()))
			break;
		for (size_t i = 0; i < gcount; ++i)
			originCode += std::bitset<8>(readBuffer[i]).to_string();
		plainCode += coderPtr->Decode(originCode);
		size_t iNextByte = writeBufferIndex = 0, buffSize = plainCode.size() / 8;
		if (buffSize > writeBlockSize) {
			writeBlockSize = buffSize;
			writeBufferSp = std::shared_ptr<char>(new char[writeBlockSize]);
			writeBuffer = writeBufferSp.get();
		}
		while ((plainCode.size() - iNextByte) > 7) {
			std::bitset<8> oneByte = std::bitset<8>(plainCode, iNextByte, 8);
			const char c = static_cast<char>(oneByte.to_ulong());
			writeBuffer[writeBufferIndex++] = c;
			iNextByte += 8;
		}
		plainCode.erase(0, iNextByte);
		if (fileSize && writedSize + writeBufferIndex > fileSize)
			writeBufferIndex = fileSize - writedSize;
		ofs.write(writeBuffer, writeBufferIndex);
		writedSize += writeBufferIndex;
	}
	if (fileSize && writedSize != fileSize)
		throw std::runtime_error("decode error(writedSize != fileSize)!");

	return 0;
}
