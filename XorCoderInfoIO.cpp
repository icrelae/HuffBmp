#include "XorCoderInfoIO.h"


XorCoderInfoIO::XorCoderInfoIO(int i)
{
	SetMgcNmb(i);
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
}

int XorCoderInfoIO::GetMgcNmb()
{
	return mgcNmb;
}
