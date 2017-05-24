#include "XorCoderInfoIO.h"


XorCoderInfoIO::XorCoderInfoIO(int i): mgcNmb(i)
{
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
