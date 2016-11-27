#pragma once
#include "BufferManager.h"
class Geometry;
class RenderInfo;

class RenderEngine
{
public:
	static void initialize();
	static void Shutdown();
	static void AddGeometry(void* vertices, unsigned vertexSize, void* indices
		, unsigned indexSize, Geometry& mesh);
	static void AddRenderInfo(RenderInfo* info);
	static void RemoveRenderInfo(RenderInfo* info);
	static void Draw(float dt, bool isPlaying);
private:
	RenderEngine();
	static void DrawAllVertexBuffers();
	BufferManager* bufferManager;
};

