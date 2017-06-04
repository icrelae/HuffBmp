#include <fstream>
#include <memory>
#include <bitset>
#include "EncodeStrategy.h"

EncodeStrategy::EncodeStrategy(CoderInfoIO *p): coderInfoPtr(p)
{
}

void EncodeStrategy::SetCoderInfoPtr(CoderInfoIO *p)
{
	coderInfoPtr = p;
}

int EncodeStrategy::Encode(const std::string &iFile, const std::string &oFile)
{
	std::ifstream ifs(iFile, std::fstream::binary);
	std::fstream ofs(oFile, std::fstream::binary | std::fstream::in | std::fstream::out);
	if (!ifs || !ofs)
		throw std::runtime_error("cannot open file!");

	size_t fileSize = GetFileSize(ifs);
	ofs.write((char*)&fileSize, sizeof(fileSize));
	if (RSLTOK != coderInfoPtr->Preprocess(ifs, ofs))
		throw std::runtime_error("preprocess error");
	ifs.clear();
	ofs.clear();
	ifs.seekg(std::fstream::beg);	// useless if seekg before clear
	ofs.seekg(std::fstream::beg);

	const Coder *coderPtr = coderInfoPtr->GetCoder();
	size_t gcount = readBlockSize, writeBufferIndex;
	std::shared_ptr<char> readBufferSp(new char[readBlockSize]);
	std::shared_ptr<char> writeBufferSp(new char[writeBlockSize]);
	char *readBuffer = readBufferSp.get();
	char *writeBuffer = writeBufferSp.get();
	std::string originCode, cipherCode;
	coderInfoPtr->WriteInfo(ofs);
	while (gcount == readBlockSize) {
		ifs.read(readBuffer, readBlockSize);
		gcount = ifs.gcount();
		for (size_t i = 0; i < gcount; ++i)
			originCode += std::bitset<8>(readBuffer[i]).to_string();
		cipherCode += coderPtr->Encode(originCode);
		if (originCode.size() !=  0)
			throw std::runtime_error("encode error(originCode != 0)!");
		writeBufferIndex = 0;
		while (cipherCode.size() > 7) {
			std::bitset<8> oneByte = std::bitset<8>(cipherCode, 0, 8);
			const char c = static_cast<char>(oneByte.to_ulong());
			writeBuffer[writeBufferIndex++] = c;
			cipherCode.erase(0, 8);
		}
		ofs.write(writeBuffer, writeBufferIndex);
	}
	if (cipherCode.size() > 0) {
		cipherCode += std::string(8 - cipherCode.size(), '0');
		std::bitset<8> oneByte = std::bitset<8>(cipherCode, 0, 8);
		const char c = static_cast<char>(oneByte.to_ulong());
		ofs.write(&c, 1);
	}

	return 0;
}

size_t EncodeStrategy::GetFileSize(std::istream &is)
{
	std::streampos pos = is.tellg();
	is.seekg(0, std::fstream::end);
	size_t fileSize = is.tellg();
	is.seekg(pos);
	return fileSize;
}
