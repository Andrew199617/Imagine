#pragma once
class RenderInfo;

class BufferInfo
{
public:
	BufferInfo();
	~BufferInfo();
	bool HasRoomForVertices(unsigned totalBytes);
	bool HasRoomForIndices(unsigned totalBytes);
	unsigned m_vert_currentByteOffset;
	unsigned m_vert_bufferSizeInBytes;
	unsigned m_vert_vertexSize;
	unsigned m_vert_ID;
	unsigned m_index_currentByteOffset;
	unsigned m_index_bufferSizeInBytes;
	unsigned m_index_indexSize;
	unsigned M_index_ID;
	int VertexFormat;
	void push(RenderInfo*);
	void remove(RenderInfo*);
	bool isEmpty() const
	{
		return (top == 0);
	}
	RenderInfo* top;
};

