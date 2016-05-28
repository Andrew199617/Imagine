#pragma once
#include "BufferManager.h"
class Geometry;
class RenderInfo;

class RenderEngine
{
public:
	static void initialize();
	static void Shutdown();
	static void AddGeometry(void* vertices, unsigned vertexCount, unsigned vertexSize
		, Geometry& mesh);
	static void AddGeometry(void* vertices, unsigned vertexCount, unsigned vertexSize, void* indices
		, unsigned indexCount, unsigned indexSize, Geometry& mesh);
	static void AddRenderInfo(RenderInfo* info);
	static void Draw();
private:
	RenderEngine();
	static void DrawAllVertexBuffers();
	BufferManager* bufferManager;
};

