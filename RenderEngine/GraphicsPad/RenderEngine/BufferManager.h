#pragma once
#include <GL\glew.h>
class BufferInfo;
class RenderInfo;
class Geometry;

class BufferManager
{
public:
	BufferManager();
	~BufferManager();
	static void Initialize();
	static void Shutdown();
	static void AddGeometry(void* vertices, unsigned vertexCount, unsigned vertexSize, Geometry& mesh);
	static void AddGeometry(void* vertices, unsigned vertexCount, unsigned vertexSize, void* indices, unsigned indexCount, unsigned indexSize, Geometry& mesh);
	static void AddRenderInfo(RenderInfo* info);
	static BufferInfo m_bufferPool[];
	static int m_numVertexBuffers;
	static int m_numIndexBuffers;

};

