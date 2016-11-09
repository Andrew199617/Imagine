#include "ImgnCollider.h"
#include "../RenderEngine/RenderInfo.h"
#include "../SpatialComponent.h"
#include "../ShapeGenerator.h"
#include "../RenderEngine/RenderEngine.h"

void ImgnCollider::DisplayCollider(std::string objName)
{
	if (renderInfo)
	{
		delete renderInfo->getTransformInfo();
		SpatialComponent* spatial = GetSiblingComponent<SpatialComponent>();
		if (spatial)
		{
			renderInfo->setTransfromInfo(new TransformInfo(center + spatial->GetPosition(), size, spatial->GetRotate()));
		}
	}
	else
	{
		renderInfo = new RenderInfo();
		renderInfo->setGeometry(ShapeGenerator::readScene(objName));
		SpatialComponent* spatial = GetSiblingComponent<SpatialComponent>();
		if (spatial)
		{
			renderInfo->setTransfromInfo(new TransformInfo(center + spatial->GetPosition(), size, spatial->GetRotate()));
		}

		FragmentShaderInfo* fragmentShader = new FragmentShaderInfo("..\\Graphicspad\\Shader\\fColliderFragmentShader.glsl");
		GLuint fId = fragmentShader->createShader();
		renderInfo->SetFragmentShaderInfo(fragmentShader);
		renderInfo->setVertexShaderInfo(new VertexShaderInfo("..\\Graphicspad\\Shader\\vColliderVertexShader.glsl"));
		renderInfo->getVertexShaderInfo()->installShader(fId);

		renderInfo->setTextureInfo(new TextureInfo());

		RenderEngine::AddRenderInfo(renderInfo);
	}

}

void ImgnCollider::Awake()
{

}

void ImgnCollider::focusInEvent(QFocusEvent * event)
{
	QWidget::focusInEvent(event);
	if (renderInfo)
	{
		renderInfo->isEnabled = true;
	}
}

void ImgnCollider::focusOutEvent(QFocusEvent * event)
{
	QWidget::focusOutEvent(event);
	if (renderInfo)
	{
		renderInfo->isEnabled = false;
	}
}