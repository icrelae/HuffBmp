#include "XorCoderInfoIO.h"


XorCoderInfoIO::XorCoderInfoIO(int i): coderPtr(new XorCoder(i))
{
	SetMgcNmb(i);
}

XorCoderInfoIO::~XorCoderInfoIO()
{
	if (coderPtr)
		delete coderPtr;
	coderPtr = nullptr;
}

std::istream& XorCoderInfoIO::ReadInfo(std::istream &is)
{
	is.read((char*)&mgcNmb, sizeof(mgcNmb));
	coderPtr->SetMgcNmb(mgcNmb);
	return is;
}

std::ostream& XorCoderInfoIO::WriteInfo(std::ostream &os)
{
	os.write((char*)&mgcNmb, sizeof(mgcNmb));
	return os;
}

int XorCoderInfoIO::SetMgcNmb(int i)
{
	if (coderPtr) {
		mgcNmb = coderPtr->SetMgcNmb(i);
		coderPtr->ResetVecMgcNmbIndex();
	}
	return mgcNmb;
}

int XorCoderInfoIO::GetMgcNmb()
{
	return mgcNmb;
}

std::istream& XorCoderInfoIO::Read(std::istream &is, char *buf, size_t size)
{
	is.read(buf, size);
	gcount = is.gcount();
	return is;
}

std::ostream& XorCoderInfoIO::Write(std::ostream &os, char *buf, size_t size)
{
	os.write(buf, size);
	return os;
}

size_t XorCoderInfoIO::Gcount()
{
	return gcount;
}

const Coder* XorCoderInfoIO::GetCoder() const
{
	return coderPtr;
}
