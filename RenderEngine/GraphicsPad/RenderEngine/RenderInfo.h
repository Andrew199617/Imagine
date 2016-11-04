#pragma once
#include <GL\glew.h>
class Geometry;
#include "TransformInfo.h"
#include "FragmentShaderInfo.h"
#include "VertexShaderInfo.h"
#include "TextureInfo.h"
#include "AnimationInfo.h"

class RenderInfo
{
public:
	RenderInfo(RenderInfo* me,RenderInfo* next);
	RenderInfo(){ isEnabled = true; }
	~RenderInfo() { delete m_transformInfo; delete m_textureInfo; 
	if (m_vertexShaderInfo) { delete m_vertexShaderInfo; }
	if (m_fragmentShaderInfo) { delete m_fragmentShaderInfo; }
	}
	void Draw(float dt, bool isPlaying);
	void SendAttributeData();
	void SendUniformData(float dt, bool isPlaying);

public:
	FragmentShaderInfo* GetFragmentShaderInfo() const { return m_fragmentShaderInfo; }
	void SetFragmentShaderInfo(FragmentShaderInfo* val) { m_fragmentShaderInfo = val; }
	void setGeometry(Geometry* geo) { m_mesh = geo;	}
	Geometry* getGeometry(){ return m_mesh; }
	void setTransfromInfo(TransformInfo* tranInfo) { m_transformInfo = tranInfo; }
	TransformInfo* getTransformInfo() { return m_transformInfo; }
	void setVertexShaderInfo(VertexShaderInfo* vertexShaderInfo) { m_vertexShaderInfo = vertexShaderInfo; }
	VertexShaderInfo* getVertexShaderInfo() { return m_vertexShaderInfo; }
	void setTextureInfo(TextureInfo* textureInfo)
	{
		if (!m_textureInfo)
			delete m_textureInfo;
		m_textureInfo = textureInfo;
	}
	TextureInfo* getTextureInfo() { return m_textureInfo; }
	RenderInfo* Next() const { return next; }
	void Next(RenderInfo* val) { next = val; }
	bool isEnabled;
private:
	Geometry* m_mesh = 0;
	TransformInfo* m_transformInfo = 0;
	VertexShaderInfo* m_vertexShaderInfo = 0;
	FragmentShaderInfo* m_fragmentShaderInfo = 0;
	TextureInfo* m_textureInfo = 0;
	RenderInfo* next;
};

