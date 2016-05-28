#pragma once
#pragma warning(push)
#pragma warning (disable:4100)
#include <noise\noise.h>
#pragma warning(pop)
#pragma warning(push)
#pragma warning (disable:4244)
#include "noise\noiseutils.h"
#pragma warning(pop)
#include <string.h>

using namespace noise;
using namespace utils;

class NoiseGenerator
{
public:
	NoiseGenerator(int = 512, int = 512);
	~NoiseGenerator();

	NoiseMap makeHeightMap();
	Image renderImage();
	Image renderBumpImage();
	void writeImage(std::string name);

	module::Perlin myModule;
private:
	int destWidth;
	int destHeight;
};

