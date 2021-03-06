#pragma once
#pragma warning(push)
#pragma warning (disable:4800)
#include "ImgnComponent.h"
#pragma warning(pop)
#include "SpatialComponent.h"
#include "RenderEngine\RenderInfo.h"
#include "ShapeGenerator.h"
#include "VertexFormats.h"

class MeshComponent : public ImgnComponent
{
	Q_OBJECT

public:
	IMGN_GENERATE(MeshComponent)
	IMGN_PROPERTY(texPath,"")
	IMGN_END(MeshComponent)

public:
	void setUpFragmentVertexShader();
	void makeShaderInfo(int vertexFormat, string objname);
	void setTransformInfo();
	void setTransformInfo(glm::vec3,glm::vec3,glm::quat);
	void setRenderInfo(string objname);
	void setNodeRenderInfo(string objname, float radius);
	void setRenderInfo_Line(glm::vec3 point1, glm::vec3 point2);
	virtual void Update(float dt) override;
	void disableEnableMesh() 
	{ 
		if(renderinfo.isEnabled) renderinfo.isEnabled = false;
		else renderinfo.isEnabled = true;
	}

	RenderInfo renderinfo;
	FragmentShaderInfo* fragmentShaderInfo = 0;
	VertexShaderInfo* vertexShaderInfo = 0;
	string vertexShaderLocation;
	string fragmentShaderLocation;

	// Inherited via ImgnComponent
	virtual void ClearFocus() override;
	virtual void SetHidden(bool) override;

	virtual void Disable(bool enabled = false) override;
	virtual void Enable(bool enabled = true) override;


	virtual void CreateWidgets() override;
	virtual void DeleteWidgets() override;
	void UpdateTextureInfo(string str);

	string GetTexPath() const { return texPath; }
	void SetTexPath(string val) { texPath = val; }
private:
	string texPath;

protected:
	virtual bool Initialize() override;


private slots:
	void UpdateTextureInfo();
};

