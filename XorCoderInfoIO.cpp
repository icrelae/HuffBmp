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
	return is;
}

std::ostream& XorCoderInfoIO::WriteInfo(std::ostream &os)
{
	os.write((char*)&mgcNmb, sizeof(mgcNmb));
	return os;
}

void XorCoderInfoIO::SetMgcNmb(int i)
{
	mgcNmb = i;
	if (coderPtr) {
		coderPtr->SetMgcNmb(i);
		coderPtr->ResetVecMgcNmbIndex();
	}
}

int XorCoderInfoIO::GetMgcNmb()
{
	return mgcNmb;
}

const Coder* XorCoderInfoIO::GetCoder() const
{
	return coderPtr;
}
