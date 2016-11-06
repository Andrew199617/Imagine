#include "BoxCollider.h"
#include "../RenderEngine/RenderInfo.h"
#include "..\ShapeGenerator.h"
#include "..\RenderEngine\RenderEngine.h"
#include "..\SpatialComponent.h"
#include "QtGui/qevent.h"


BoxCollider::~BoxCollider()
{

}

bool BoxCollider::Initialize()
{
	renderInfo = 0;
	spatial = GetSiblingComponent<SpatialComponent>();
	size = spatial->GetScale() + glm::vec3(.1f,.1f,.1f);
	collisionData = new Imgn::CollisionData;
	Imgn::ImgnProperties::Instance()->GetAllComponentData(collisionData);
	return true;
}

void BoxCollider::Update(float)
{
	for (int currentCollider = 0; currentCollider < collisionData->numComponents; ++currentCollider)
	{
		
	}
}

void BoxCollider::Draw(float)
{
	/*if(!renderInfo)
	{
		renderInfo = new RenderInfo();
		std::string objName = "Cube";
		renderInfo->setGeometry(ShapeGenerator::readScene(objName));
		glm::vec3* vec = renderInfo->getGeometry()->centerOfMass;
		renderInfo->setTransfromInfo(new TransformInfo(center + spatial->position, size, spatial->GetRotate()));

		FragmentShaderInfo* fragmentShader = new FragmentShaderInfo("..\\Graphicspad\\Shader\\fColliderFragmentShader.glsl");
		GLuint fId = fragmentShader->createShader();
		renderInfo->SetFragmentShaderInfo(fragmentShader);
		renderInfo->setVertexShaderInfo(new VertexShaderInfo("..\\Graphicspad\\Shader\\vColliderVertexShader.glsl"));
		renderInfo->getVertexShaderInfo()->installShader(fId);

		renderInfo->setTextureInfo(new TextureInfo());

		RenderEngine::AddRenderInfo(renderInfo);
		renderInfo->isEnabled = false;
	}
	renderInfo->Draw(dt,true);*/
}

void BoxCollider::DrawBox()
{
	if (renderInfo)
	{
		delete renderInfo->getTransformInfo();
		renderInfo->setTransfromInfo(new TransformInfo(center + spatial->position, size, spatial->GetRotate()));
	}
	else
	{
		renderInfo = new RenderInfo();
		std::string objName = "Cube";
		renderInfo->setGeometry(ShapeGenerator::readScene(objName));
		//glm::vec3* vec = renderInfo->getGeometry()->centerOfMass;
		renderInfo->setTransfromInfo(new TransformInfo(center + spatial->position, size, spatial->GetRotate()));

		FragmentShaderInfo* fragmentShader = new FragmentShaderInfo("..\\Graphicspad\\Shader\\fColliderFragmentShader.glsl");
		GLuint fId = fragmentShader->createShader();
		renderInfo->SetFragmentShaderInfo(fragmentShader);
		renderInfo->setVertexShaderInfo(new VertexShaderInfo("..\\Graphicspad\\Shader\\vColliderVertexShader.glsl"));
		renderInfo->getVertexShaderInfo()->installShader(fId);

		renderInfo->setTextureInfo(new TextureInfo());

		RenderEngine::AddRenderInfo(renderInfo);
	}
	
}

void BoxCollider::OnValueChange(std::string VariableName)
{
	if (VariableName == "Center" || VariableName == "Size")
	{
		DrawBox();
	}
}

void BoxCollider::focusInEvent(QFocusEvent * event)
{
	QWidget::focusInEvent(event);
	if (renderInfo)
	{
		renderInfo->isEnabled = true;
	}
}

void BoxCollider::focusOutEvent(QFocusEvent * event)
{
	QWidget::focusOutEvent(event);
	if (renderInfo)
	{
		renderInfo->isEnabled = false;
	}
}

