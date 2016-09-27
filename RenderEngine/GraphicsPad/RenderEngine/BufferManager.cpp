#include "BufferManager.h"
#include "BufferInfo.h"
#pragma warning(push)
#pragma warning(disable : 4201)
#include "Geometry.h"
#include "RenderInfo.h"
#include "..\VertexFormats.h"
#pragma warning(pop)
#define MEGABYTE (1048576 * 14)

int BufferManager::m_numVertexBuffers = 0;
int BufferManager::m_numIndexBuffers = 0;
BufferInfo BufferManager::m_bufferPool[] = {
	BufferInfo(), BufferInfo(), BufferInfo(), BufferInfo(), BufferInfo(), BufferInfo(), BufferInfo(),
};

BufferManager::BufferManager()
{
	
}


BufferManager::~BufferManager()
{
	for (int i = 0; i < m_numVertexBuffers; i++)
	{
		glDeleteBuffers(1, &m_bufferPool[i].m_vert_ID);
	}
	for (int i = 0; i < m_numIndexBuffers; i++)
	{
		glDeleteBuffers(1, &m_bufferPool[i].M_index_ID);
	}
}

void BufferManager::Initialize()
{
	m_bufferPool[m_numVertexBuffers].VertexFormat = 0;
	glGenBuffers(1, &m_bufferPool[m_numVertexBuffers].m_vert_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferPool[m_numVertexBuffers].m_vert_ID);
	glBufferData(GL_ARRAY_BUFFER, MEGABYTE, 0, GL_STATIC_DRAW);
	m_bufferPool[m_numVertexBuffers].m_vert_bufferSizeInBytes = MEGABYTE;

	glGenBuffers(1, &m_bufferPool[m_numIndexBuffers].M_index_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferPool[m_numIndexBuffers].M_index_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, MEGABYTE, 0, GL_STATIC_DRAW);
	m_bufferPool[m_numIndexBuffers].m_index_bufferSizeInBytes = MEGABYTE;
}

void BufferManager::Shutdown()
{

}

void BufferManager::AddGeometry(void* vertices, unsigned vertexCount, unsigned vertexSize, Geometry& mesh)
{
	vertexCount;
	if (!m_bufferPool[m_numVertexBuffers].HasRoomForVertices(vertexSize))
	{
		m_numVertexBuffers++;
		m_numIndexBuffers++;
		Initialize();
	}

	mesh.m_vertexId = m_bufferPool[m_numVertexBuffers].m_vert_ID;
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferPool[m_numVertexBuffers].m_vert_ID);
	glBufferSubData(GL_ARRAY_BUFFER, m_bufferPool[m_numVertexBuffers].m_vert_currentByteOffset, vertexSize, vertices);
	mesh.m_vertexByteOffset = m_bufferPool[m_numVertexBuffers].m_vert_currentByteOffset;
	m_bufferPool[m_numVertexBuffers].m_vert_currentByteOffset += vertexSize;
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
}

void BufferManager::AddGeometry(void* vertices, unsigned vertexCount, unsigned vertexSize, void* indices, unsigned indexCount, unsigned indexSize, Geometry& mesh)
{
	vertexCount;
	indexCount;
	if (!m_bufferPool[m_numVertexBuffers].HasRoomForVertices(vertexSize) ||
		!m_bufferPool[m_numIndexBuffers].HasRoomForIndices(indexSize) ||
		m_bufferPool[m_numVertexBuffers].VertexFormat != mesh.VertexFormat )
	{
		m_numVertexBuffers++;
		m_numIndexBuffers++;
		Initialize();
	}

	if (m_bufferPool[m_numVertexBuffers].VertexFormat == 0)
	{
		m_bufferPool[m_numVertexBuffers].VertexFormat = mesh.VertexFormat;

		
	}

	if (mesh.VertexFormat & HasTexture)
	{
		
	}
	
	mesh.m_vertexId = m_bufferPool[m_numVertexBuffers].m_vert_ID;
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferPool[m_numVertexBuffers].m_vert_ID);
	glBufferSubData(GL_ARRAY_BUFFER, m_bufferPool[m_numVertexBuffers].m_vert_currentByteOffset, vertexSize, vertices);
	mesh.m_vertexByteOffset = m_bufferPool[m_numVertexBuffers].m_vert_currentByteOffset;
	m_bufferPool[m_numVertexBuffers].m_vert_currentByteOffset += vertexSize;
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	mesh.m_indexId = m_bufferPool[m_numIndexBuffers].M_index_ID;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferPool[m_numIndexBuffers].M_index_ID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, m_bufferPool[m_numIndexBuffers].m_index_currentByteOffset, indexSize, indices);
	mesh.m_indexByteOffset = m_bufferPool[m_numIndexBuffers].m_index_currentByteOffset;
	m_bufferPool[m_numIndexBuffers].m_index_currentByteOffset += indexSize;
	
}

void BufferManager::AddRenderInfo(RenderInfo* info)
{
	for (int i = 0; i <= m_numVertexBuffers; i++)
	{
		if (m_bufferPool[i].m_vert_ID == info->getGeometry()->m_vertexId &&
			m_bufferPool[i].M_index_ID == info->getGeometry()->m_indexId)
		{
			m_bufferPool[i].push(info);
		}
	}
}

void BufferManager::RemoveRenderInfo()
{
	for (int i = 0; i < m_numVertexBuffers; i++)
	{
		glDeleteBuffers(1, &m_bufferPool[i].m_vert_ID);
	}
	for (int i = 0; i < m_numIndexBuffers; i++)
	{
		glDeleteBuffers(1, &m_bufferPool[i].M_index_ID);
		m_bufferPool[i] = BufferInfo();
	}
	m_numVertexBuffers = 0;
	m_numIndexBuffers = 0;
	//Initialize();
}





