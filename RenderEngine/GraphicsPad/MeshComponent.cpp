#include "MeshComponent.h"
#include "RenderEngine\RenderEngine.h"
#include "gtc\matrix_transform.hpp"
#include "gtx\transform.hpp"

MeshComponent::MeshComponent()
{
}


MeshComponent::~MeshComponent()
{
	//delete renderinfo;
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
		vertexShaderLocation = ConfigReader::findValueForKey(objname+ "VertexShader");
	if (vertexShaderLocation != "0")
		vertexShaderInfo.shaderLocation = vertexShaderLocation.c_str();
	
	if (fragmentShaderLocation == "")
	fragmentShaderLocation = ConfigReader::findValueForKey(objname + "FragmentShader");
	if (fragmentShaderLocation != "0")
		fragmentShaderInfo.shaderLocation = fragmentShaderLocation.c_str();
	
}

void MeshComponent::setRenderInfo(string objname)
{
	
	renderinfo.setGeometry(ShapeGenerator::readScene(objname));
	if (objname == "batman") 
	{
		renderinfo.setTransfromInfo(new TransformInfo(this->GetSiblingComponent<SpatialComponent>()->position
			, glm::vec3(.04f, .04f, .04f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	else if (objname == "StormTropper")
	{
		renderinfo.setTransfromInfo(new TransformInfo(this->GetSiblingComponent<SpatialComponent>()->position
			, glm::vec3(2.0f, 2.0f, 2.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	else if (objname == "Arrow")
	{
		renderinfo.setTransfromInfo(new TransformInfo(this->GetSiblingComponent<SpatialComponent>()->position
				, glm::vec3(2.5f, 2.5f, 2.5f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	else if (objname == "cubePurple")
	{
		renderinfo.setTransfromInfo(new TransformInfo(this->GetSiblingComponent<SpatialComponent>()->position
			, glm::vec3(.3f, .3f, .3f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	else
		renderinfo.setTransfromInfo(new TransformInfo(this->GetSiblingComponent<SpatialComponent>()->position, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	makeShaderInfo(renderinfo.getGeometry()->VertexFormat, objname);
	setUpFragmentVertexShader();
	renderinfo.setVertexShaderInfo(&vertexShaderInfo);
	renderinfo.setTextureInfo(new TextureInfo(renderinfo.getGeometry()->texturePath,objname));
	renderinfo.getTextureInfo()->SendData(renderinfo.getVertexShaderInfo()->uTextureUL, renderinfo.getVertexShaderInfo()->uBumpMapUL);
}

void MeshComponent::setNodeRenderInfo(string objname, float radius)
{
	renderinfo.setGeometry(ShapeGenerator::readScene(objname));
	renderinfo.setTransfromInfo(new TransformInfo(GetSiblingComponent<SpatialComponent>()->position, glm::vec3(radius, radius,radius), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	makeShaderInfo(renderinfo.getGeometry()->VertexFormat, objname);
	setUpFragmentVertexShader();
	renderinfo.setVertexShaderInfo(&vertexShaderInfo);
	renderinfo.setTextureInfo(new TextureInfo(renderinfo.getGeometry()->texturePath,objname));
}

void MeshComponent::setRenderInfo_Line(glm::vec3 point1, glm::vec3 point2)
{
	renderinfo.setGeometry(ShapeGenerator::makeLine(point1,point2));
	renderinfo.setTransfromInfo(new TransformInfo(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	makeShaderInfo(renderinfo.getGeometry()->VertexFormat, "noname");
	setUpFragmentVertexShader();
	renderinfo.setVertexShaderInfo(&vertexShaderInfo);
	renderinfo.setTextureInfo(new TextureInfo(renderinfo.getGeometry()->texturePath,""));
}

bool MeshComponent::Update(float dt)
{

	renderinfo.getTransformInfo()->m_translateTransform = glm::translate(GetSiblingComponent<SpatialComponent>()->position);

	dt;
	return true;
}
