#include <random>
#include <ctime>
#include "BmpFactory.h"

namespace {
	/* static function */
	void GetRGB(const double value, unsigned char &red,
			unsigned char &green, unsigned char &blue)
	{
		// 256 * 6 + 255 = 1791
		unsigned colorInt = value * 1791;
		unsigned char bracket = colorInt / 256;
		unsigned char color = colorInt % 256;
		red = green = blue = 0;
		switch (bracket) {
		case 0:
			red = color;
			break;
		case 1:
			red = 255;
			green = color;
			break;
		case 2:
			red = 255 - color;
			green = 255;
			break;
		case 3:
			green = 255;
			blue = color;
			break;
		case 4:
			green = 255 - color;
			blue = 255;
			break;
		case 5:
			red = color;
			blue = 255;
			break;
		case 6:
			red = 255 - color;
			blue = 255 - color;
			break;
		default:
			break;
		}
	}
}

BmpFactory::BmpFactory()
{
	bmpFileHdr.bfReserved1 = 0x4248;	// HB
	bmpFileHdr.bfOffBits = 54;
	bmpInfoHdr.biWidth = 1920;
	bmpInfoHdr.biHeight = 1080;
	bmpInfoHdr.biBitPerPxl = 24;
	bmpInfoHdr.biXPxlsPerMeter = 0;
	bmpInfoHdr.biYPxlsPerMeter = 0;
	UpdateBmpHeader();
}

void BmpFactory::UpdateBmpHeader()
{
	bmpInfoHdr.biImageSize = bmpInfoHdr.GetBiImageSize();
	bmpFileHdr.bfSize = bmpFileHdr.bfOffBits + bmpInfoHdr.biImageSize;
}

bool BmpFactory::GetFile(const std::string fileName, const std::ios_base::openmode mode)
{
	std::fstream bmpFile(fileName, mode);

	// get mandelbrot value map
	std::default_random_engine engine(time(0));
	std::uniform_real_distribution<double>
		dist(mandelbrot.GetZoomFactor(), mandelbrot.GetZoomFactor()+1);
	mandelbrot.SetZoomFactor(dist(engine));
	std::shared_ptr<double> mdbValMap =
		mandelbrot.GetMdbValMap(bmpInfoHdr.biWidth, bmpInfoHdr.biHeight);
	const double *mdbValMapPtr = mdbValMap.get();

	/* new unsigned array(size is iteration) and initialize with 0
	 * histogram is using to statistic the ratio of diffrent value in mdbValMap
	 * the value in mdbValMap won't greater than 'iteration-1' */
	const size_t interation = mandelbrot.GetIteration();
	const size_t resolution = bmpInfoHdr.biWidth * bmpInfoHdr.biHeight;
	std::unique_ptr<double[]> histogram(new double[interation+1]{0});
	for (size_t i = 0; i < resolution; ++i)
		++histogram[static_cast<size_t>(mdbValMapPtr[i])];
	// 'histogram[0]' equal to 0;
	// redundant last element of histogram using for prevent out-of-range
	// when get value using 'histogram[mdbValue + 1]';
	for (size_t i = 1; i < interation+1; ++i)
		histogram[i] = histogram[i-1] + histogram[i] / resolution;

	// convert mandelbrot value to RGB according to histogram
	std::unique_ptr<unsigned char[]> image(new unsigned char[resolution * 3]{0});
	for (size_t i = 0; i < resolution; ++i) {
		const size_t mdbValue = static_cast<size_t>(mdbValMapPtr[i]);
		double colorCode = histogram[mdbValue];
		colorCode += (mdbValMapPtr[i] - mdbValue) *
			(histogram[mdbValue + 1] - histogram[mdbValue]);
		// sequence of color in bitmap is BGR
		GetRGB(colorCode, image[i*3+2], image[i*3+1], image[i*3]);
	}

	bmpFileHdr.WriteHeader(bmpFile);
	bmpInfoHdr.WriteHeader(bmpFile);
	bmpFile.write(reinterpret_cast<char*>(image.get()), resolution*3);

	return true;
}

void BmpFactory::SetBitPerPxl(const size_t bits)
{
	bmpInfoHdr.biBitPerPxl = bits;
	UpdateBmpHeader();
}

void BmpFactory::SetResolution(const size_t width, const size_t height)
{
	bmpInfoHdr.biWidth = width;
	bmpInfoHdr.biHeight = height;
	UpdateBmpHeader();
}
