#ifndef _BMPCODERINFOIO_H
#define _BMPCODERINFOIO_H
// 2017.06.09 21:22

#include <bitset>
#include "CoderInfoIO.h"
#include "BmpCoder.h"

class BmpCoderInfoIO: CoderInfoIO {
public:
	virtual std::istream& ReadInfo(std::istream&) override;
	virtual std::ostream& WriteInfo(std::ostream&) override;
	virtual std::istream& Read(std::istream&, char*, size_t) override;
	virtual std::ostream& Write(std::ostream&, char*, size_t) override;
	virtual size_t Gcount() const override;
	// for decode, check only instream
	virtual enum PreprcsRslt Preprocess(std::istream&) override;
	// for encode, check both instream and outstream
	virtual enum PreprcsRslt Preprocess(std::istream&, std::iostream&) override;
	virtual const Coder* GetCoder() const override;

	void ReadBmpFileHeader(std::istream&);
	void ReadBmpInfoHeader(std::istream&);
	static void ReadBmpFileHeader(std::istream&, BmpFileHeader&);
	static void ReadBmpInfoHeader(std::istream&, BmpInfoHeader&);
	static void WriteBmpFileHeader(std::ostream&, BmpFileHeader&);
	static void WriteBmpInfoHeader(std::ostream&, BmpInfoHeader&);
	BmpFileHeader bmpFileHdr;
	BmpInfoHeader bmpInfoHdr;
private:
	size_t gcount;
	BmpCoder *coderPtr;
	char mask;

	bool IsValidBmp(const BmpFileHeader&, const BmpInfoHeader&);
};

#endif // _BMPCODERINFOIO_H

