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

const Coder* XorCoderInfoIO::GetCoder() const
{
	return coderPtr;
}
