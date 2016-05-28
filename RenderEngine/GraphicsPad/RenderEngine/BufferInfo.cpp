#include "BufferInfo.h"
#include "RenderInfo.h"
#include <iostream>

BufferInfo::BufferInfo()
{
	m_vert_currentByteOffset = 0;
	m_index_currentByteOffset = 0;
	top = 0;
}


BufferInfo::~BufferInfo()
{
	while (!isEmpty()){
		pop();
	}
}

bool BufferInfo::HasRoomForVertices(unsigned totalBytes)
{
	if (m_vert_currentByteOffset + totalBytes >= m_vert_bufferSizeInBytes)
	{
		return false;
	}
	return true;
}

bool BufferInfo::HasRoomForIndices(unsigned totalBytes)
{
	if (m_index_currentByteOffset + totalBytes >= m_index_bufferSizeInBytes)
	{
		return false;
	}
	return true;
}

void BufferInfo::push(RenderInfo* var)
{
	RenderInfo* node = var;
	node->Next(top);
	node->isEnabled = true;
	top = node;
}

const void BufferInfo::pop()
{
	if (top)
	{
		RenderInfo* nextTop = top->Next();
		
		//delete top;
		top = nextTop;
	}
}