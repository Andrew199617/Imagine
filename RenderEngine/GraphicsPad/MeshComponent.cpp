#include "MeshComponent.h"
#include "RenderEngine\RenderEngine.h"
#include "gtc\matrix_transform.hpp"
#include "gtx\transform.hpp"

MeshComponent::MeshComponent() : ImgnComponent()
{
}


MeshComponent::~MeshComponent()
{
}

void MeshComponent::setUpFragmentVertexShader()
{
	GLuint fragmentShaderID = fragmentShaderInfo.createShader();
	vertexShaderInfo.installShader(fragmentShaderID);
}

void MeshComponent::makeShaderInfo(int vertexFormat, string objname)
{

	switch (vertexFormat)
	{
	case PositionOnly:
		vertexShaderInfo = VertexShaderInfo();
		fragmentShaderInfo = FragmentShaderInfo();
		break;
	case PositionColor:
		vertexShaderInfo = VertexShaderInfo();
		fragmentShaderInfo = FragmentShaderInfo();
		break;
	case PositionColorNormal:
		vertexShaderInfo = VertexShaderInfo();
		fragmentShaderInfo = FragmentShaderInfo();
		break;
	case PositionColorTexture:
		vertexShaderInfo = VertexShaderInfo();
		fragmentShaderInfo = FragmentShaderInfo("..\\GraphicsPad\\Shader\\ctFragmentShaderCode.glsl");
		break;
	case PositionTexture:
		vertexShaderInfo = VertexShaderInfo();
		fragmentShaderInfo = FragmentShaderInfo("..\\GraphicsPad\\Shader\\tFragmentShaderCode.glsl");
		break;
	case PositionNormal:
		vertexShaderInfo = VertexShaderInfo();
		fragmentShaderInfo = FragmentShaderInfo();
		break;
	case PositionTextureNormal:
		vertexShaderInfo = VertexShaderInfo();
		fragmentShaderInfo = FragmentShaderInfo("..\\GraphicsPad\\Shader\\tFragmentShaderCode.glsl");
		break;
	case PositionColorTextureNormal:
		vertexShaderInfo = VertexShaderInfo();
		fragmentShaderInfo = FragmentShaderInfo("..\\GraphicsPad\\Shader\\ctFragmentShaderCode.glsl");
		break;
	}
	if (vertexShaderLocation == "")
		vertexShaderLocation = ConfigReader::Instance()->findValueForKey(objname+ "VertexShader");
	if (vertexShaderLocation != "0")
		vertexShaderInfo.shaderLocation = vertexShaderLocation.c_str();
	
	if (fragmentShaderLocation == "")
	fragmentShaderLocation = ConfigReader::Instance()->findValueForKey(objname + "FragmentShader");
	if (fragmentShaderLocation != "0")
		fragmentShaderInfo.shaderLocation = fragmentShaderLocation.c_str();
	
}

void MeshComponent::setTransformInfo()
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (spatial)
	{
		renderinfo.setTransfromInfo(new TransformInfo(spatial->GetPosition(), spatial->GetScale(), spatial->GetRotate()));
	}
}

void MeshComponent::setTransformInfo(glm::vec3 position, glm::vec3 scale, glm::quat rotation)
{
	renderinfo.setTransfromInfo(new TransformInfo(position, scale, rotation));
}

void MeshComponent::setRenderInfo(string objname)
{
	renderinfo.setGeometry(ShapeGenerator::readScene(objname));
	makeShaderInfo(renderinfo.getGeometry()->VertexFormat, objname);
	setUpFragmentVertexShader();
	renderinfo.setVertexShaderInfo(&vertexShaderInfo);
	renderinfo.setTextureInfo(new TextureInfo(renderinfo.getGeometry()->texturePath,objname));
	renderinfo.getTextureInfo()->SendData();
}

void MeshComponent::setNodeRenderInfo(string objname, float radius)
{
	SpatialComponent* spatial = GetSiblingComponent<SpatialComponent>();
	renderinfo.setGeometry(ShapeGenerator::readScene(objname));
	if(spatial)
		renderinfo.setTransfromInfo(new TransformInfo(spatial->GetPosition(), glm::vec3(radius, radius,radius), spatial->GetRotate()));
	makeShaderInfo(renderinfo.getGeometry()->VertexFormat, objname);
	setUpFragmentVertexShader();
	renderinfo.setVertexShaderInfo(&vertexShaderInfo);
	renderinfo.setTextureInfo(new TextureInfo(renderinfo.getGeometry()->texturePath,objname));
}

void MeshComponent::setRenderInfo_Line(glm::vec3 point1, glm::vec3 point2)
{
	renderinfo.setGeometry(ShapeGenerator::makeLine(point1,point2));
	renderinfo.setTransfromInfo(new TransformInfo(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::quat()));
	makeShaderInfo(renderinfo.getGeometry()->VertexFormat, "noname");
	setUpFragmentVertexShader();
	renderinfo.setVertexShaderInfo(&vertexShaderInfo);
	renderinfo.setTextureInfo(new TextureInfo(renderinfo.getGeometry()->texturePath,""));
}

void MeshComponent::Update(float)
{
}

void MeshComponent::ClearFocus()
{
}

void MeshComponent::SetHidden(bool)
{
}

void MeshComponent::Disable(bool enabled /*= false*/)
{
	renderinfo.isEnabled = enabled;
}

void MeshComponent::Enable(bool enabled /*= true*/)
{
	renderinfo.isEnabled = enabled;
}

void MeshComponent::CreateWidgets()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void MeshComponent::DeleteWidgets()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool MeshComponent::Initialize()
{
	throw std::logic_error("The method or operation is not implemented.");
}
