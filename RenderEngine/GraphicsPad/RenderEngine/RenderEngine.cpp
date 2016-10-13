#include "RenderEngine.h"
#include "BufferManager.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include "Geometry.h"
#include "RenderInfo.h"
#pragma warning(pop)
#include "BufferInfo.h"


RenderEngine::RenderEngine()
{
}

void RenderEngine::DrawAllVertexBuffers()
{

}

void RenderEngine::initialize()
{
	BufferManager::Initialize();
}

void RenderEngine::Shutdown()
{
	BufferManager::Shutdown();
}

void RenderEngine::AddGeometry(void* vertices, unsigned vertexCount, unsigned vertexSize, Geometry& mesh)
{
	BufferManager::AddGeometry(vertices, vertexCount, vertexSize, mesh);
}

void RenderEngine::AddGeometry(void* vertices, unsigned vertexCount, unsigned vertexSize, void* indices
	, unsigned indexCount, unsigned indexSize, Geometry& mesh)
{
	BufferManager::AddGeometry(vertices, vertexCount, vertexSize,indices,indexCount,indexSize, mesh);

}

void RenderEngine::AddRenderInfo(RenderInfo* info)
{
	BufferManager::AddRenderInfo(info);
}

void RenderEngine::RemoveRenderInfo()
{
	BufferManager::RemoveRenderInfo();
}

void RenderEngine::Draw(float dt,bool isPlaying)
{
	for (int i = 0; i <= BufferManager::m_numVertexBuffers; i++)
	{
		if (!BufferManager::m_bufferPool[i].isEmpty())
			BufferManager::m_bufferPool[i].top->Draw(dt,isPlaying);
	}

}

