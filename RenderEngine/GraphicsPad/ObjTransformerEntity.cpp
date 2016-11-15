#include "ObjTransformerEntity.h"
#include "MeshComponent.h"
#include "RenderEngine\RenderEngine.h"
#include "Physics\PhysicsTypeDefs.hpp"



ObjTransformerEntity::ObjTransformerEntity()
{
}


ObjTransformerEntity::~ObjTransformerEntity()
{
}

bool ObjTransformerEntity::Initialize()
{
	scale = glm::vec3(.5, .5, .5);
	SetName("ObjectTransformer");
	//objectTransformerMouse = new MouseComponent;
	xMesh = new MeshComponent;
	yMesh = new MeshComponent;
	zMesh = new MeshComponent;

	AddComponent(xMesh, "MovementMesh");
	AddComponent(yMesh, "RotatorMesh");
	AddComponent(zMesh, "ScalerMesh");
	position = glm::vec3(0, 10, 0);

	return true;
}

void ObjTransformerEntity::SendDataToOpenGl()
{
	xMesh->renderinfo.setGeometry(ShapeGenerator::readScene("Arrow"));
	xMesh->renderinfo.getGeometry()->VertexFormat = HasPosition;
	xMesh->vertexShaderInfo = VertexShaderInfo();
	xMesh->fragmentShaderInfo = FragmentShaderInfo("..\\Graphicspad\\Shader\\ctFragmentShaderCode.glsl");
	xMesh->setUpFragmentVertexShader();
	xMesh->renderinfo.setVertexShaderInfo(&xMesh->vertexShaderInfo);
	xMesh->renderinfo.setTextureInfo(new TextureInfo());
	xMesh->renderinfo.color = glm::vec3(1, 0, 0);
	
	glm::vec3 rotateInRadians = glm::vec3(0, 0, 270 * R_PI / 180);
	xMesh->setTransformInfo(position + (glm::vec3(5, 0, 0) * scale), scale, glm::quat(rotateInRadians));

	yMesh->renderinfo.setGeometry(ShapeGenerator::readScene("Arrow"));
	yMesh->renderinfo.getGeometry()->VertexFormat = HasPosition;
	yMesh->vertexShaderInfo = VertexShaderInfo();
	yMesh->fragmentShaderInfo = FragmentShaderInfo("..\\Graphicspad\\Shader\\ctFragmentShaderCode.glsl");
	yMesh->setUpFragmentVertexShader();
	yMesh->renderinfo.setVertexShaderInfo(&xMesh->vertexShaderInfo);
	yMesh->renderinfo.setTextureInfo(new TextureInfo());
	yMesh->renderinfo.color = glm::vec3(0, 1, 0);
	yMesh->setTransformInfo(position + (glm::vec3(0, 5, 0) * scale), scale, glm::quat(glm::vec3()));

	zMesh->renderinfo.setGeometry(ShapeGenerator::readScene("Arrow"));
	zMesh->renderinfo.getGeometry()->VertexFormat = HasPosition;
	zMesh->vertexShaderInfo = VertexShaderInfo();
	zMesh->fragmentShaderInfo = FragmentShaderInfo("..\\Graphicspad\\Shader\\ctFragmentShaderCode.glsl");
	zMesh->setUpFragmentVertexShader();
	zMesh->renderinfo.setVertexShaderInfo(&xMesh->vertexShaderInfo);
	zMesh->renderinfo.setTextureInfo(new TextureInfo());
	zMesh->renderinfo.color = glm::vec3(0, 0, 1);

	rotateInRadians = glm::vec3(90 * R_PI / 180, 0, 0);
	zMesh->setTransformInfo(position + (glm::vec3(0, 0, 5) * scale), scale, glm::quat(rotateInRadians));

	RenderEngine::AddRenderInfo(&xMesh->renderinfo);
	RenderEngine::AddRenderInfo(&yMesh->renderinfo);
	RenderEngine::AddRenderInfo(&zMesh->renderinfo);
}
