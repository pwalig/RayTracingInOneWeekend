#include "image.hpp"

#define __STDC_LIB_EXT1__
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

rt::pixel& rt::image::at(u32 X, u32 Y)
{
	return pdata[Y * width + X];
}

const rt::pixel& rt::image::at(u32 X, u32 Y) const
{
	return pdata[Y * width + X];
}

rt::image::image(u32 Width, u32 Height)
	: pdata(new pixel[Width * Height]),
	width(Width), height(Height) { }

rt::image::image(const matrix<glm::vec3>& Hdr) :
	pdata(new pixel[Hdr.x() * Hdr.y()]),
	width(Hdr.x()), height(Hdr.y())
{
	for (u32 i = 0; i < width; ++i)
		for (u32 j = 0; j < height; ++j)
			at(i, j) = pixel(Hdr[i][j]);
}

rt::image::~image()
{
	delete[] pdata;
}

void rt::image::to_png(const char* filename) const
{
	stbi_write_png(filename, width, height, 3, pdata, width * 3);
}

void rt::image::to_jpg(const char* filename) const
{
	stbi_write_jpg(filename, width, height, 3, pdata, 50);
}
