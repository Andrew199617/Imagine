#include "NoiseGenerator.h"



NoiseGenerator::NoiseGenerator(int DestWidth, int DestHeight)
{
	destWidth = DestWidth;
	destHeight = DestHeight;
}


NoiseGenerator::~NoiseGenerator()
{
}

NoiseMap NoiseGenerator::makeHeightMap()
{
	NoiseMap heightMap;

	NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(destWidth, destHeight);
	heightMapBuilder.SetBounds(2.0, 6.0, 1.0, 5.0);
	heightMapBuilder.Build();

	return heightMap;
}

Image NoiseGenerator::renderImage()
{
	Image image;
	NoiseMap heightMap = makeHeightMap();

	RendererImage renderer;
	renderer.SetSourceNoiseMap(heightMap);
	renderer.SetDestImage(image);
	renderer.ClearGradient();
	renderer.AddGradientPoint(-1.0000, utils::Color(0, 0, 128, 255)); // deeps
	renderer.AddGradientPoint(-0.2500, utils::Color(0, 0, 255, 255)); // shallow
	renderer.AddGradientPoint(0.0000, utils::Color(0, 128, 255, 255)); // shore
	renderer.AddGradientPoint(0.0625, utils::Color(240, 240, 64, 255)); // sand
	renderer.AddGradientPoint(0.1250, utils::Color(32, 160, 0, 255)); // grass
	renderer.AddGradientPoint(0.3750, utils::Color(224, 224, 0, 255)); // dirt
	renderer.AddGradientPoint(0.7500, utils::Color(128, 128, 128, 255)); // rock
	renderer.AddGradientPoint(1.0000, utils::Color(255, 255, 255, 255)); // snow
	renderer.EnableLight();
	renderer.SetLightContrast(3.0); // Triple the contrast
	renderer.SetLightBrightness(2.0); // Double the brightness
	renderer.Render();

	return image;
}

Image NoiseGenerator::renderBumpImage()
{
	Image image;
	NoiseMap heightMap = makeHeightMap();

	RendererImage renderer;
	renderer.SetSourceNoiseMap(heightMap);
	renderer.SetDestImage(image);
	renderer.ClearGradient();
	renderer.AddGradientPoint(-1.0000, utils::Color(0, 0, 0, 255)); // deeps
	renderer.AddGradientPoint(-0.2500, utils::Color(0, 0, 0, 255)); // shallow
	renderer.AddGradientPoint(0.0000, utils::Color(5, 5, 5, 255)); // shore
	renderer.AddGradientPoint(0.0625, utils::Color(10, 10, 10, 255)); // sand
	renderer.AddGradientPoint(0.1250, utils::Color(15, 15, 15, 255)); // grass
	renderer.AddGradientPoint(0.3750, utils::Color(25, 25, 25, 255)); // dirt
	renderer.AddGradientPoint(0.7500, utils::Color(100, 100, 100, 255)); // rock
	renderer.AddGradientPoint(1.0000, utils::Color(200, 200, 200, 255)); // snow
	renderer.EnableLight();
	renderer.SetLightContrast(3.0); // Triple the contrast
	renderer.SetLightBrightness(2.0); // Double the brightness
	renderer.Render();

	return image;
}

void NoiseGenerator::writeImage(std::string name)
{
	Image image = renderImage();
	WriterBMP writer;
	writer.SetSourceImage(image);
	writer.SetDestFilename("..\\..\\StaticData\\Texture\\"+ name +".bmp");
	writer.WriteDestFile();

	image = renderBumpImage();
	writer.SetSourceImage(image);
	writer.SetDestFilename("..\\..\\StaticData\\Texture\\" + name + "_bump.bmp");
	writer.WriteDestFile();
}



