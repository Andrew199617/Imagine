#pragma once
#include "Component.h"
#include "SpatialComponent.h"
#include "RenderEngine\RenderInfo.h"
#include "RenderEngine\VertexShaderInfo.h"
#include "RenderEngine\FragmentShaderInfo.h"
#include "ShapeGenerator.h"
#include "RenderEngine\TransformInfo.h"
#include "VertexFormats.h"
#include "RenderEngine\TextureInfo.h"

class MeshComponent :
	public Component
{
public:
	MeshComponent();
	~MeshComponent();
	void setUpFragmentVertexShader();
	void makeShaderInfo(int vertexFormat, string objname);
	void setTransformInfo();
	void setRenderInfo(string objname);
	void setNodeRenderInfo(string objname, float radius);
	void setRenderInfo_Line(glm::vec3 point1, glm::vec3 point2);
	virtual bool Update(float dt) override;
	void disableEnableMesh() 
	{ 
		if(renderinfo.isEnabled) renderinfo.isEnabled = false;
		else renderinfo.isEnabled = true;
	}

	RenderInfo renderinfo;
	FragmentShaderInfo fragmentShaderInfo;
	VertexShaderInfo vertexShaderInfo;
	string vertexShaderLocation;
	string fragmentShaderLocation;
};

