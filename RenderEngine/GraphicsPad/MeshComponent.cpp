#include "MeshComponent.h"
#include "RenderEngine\RenderEngine.h"
#include "gtc\matrix_transform.hpp"
#include "gtx\transform.hpp"
#include "Qt\qboxlayout.h"
#include "QtGui\QLabel"
#include "Qt\qpushbutton.h"

MeshComponent::MeshComponent() : ImgnComponent()
{
}

MeshComponent::~MeshComponent()
{
	if (fragmentShaderInfo)
	{
		delete fragmentShaderInfo;
	}
}

void MeshComponent::setUpFragmentVertexShader()
{
	GLuint fragmentShaderID = fragmentShaderInfo->createShader();
	vertexShaderInfo->installShader(fragmentShaderID);
}

void MeshComponent::makeShaderInfo(int vertexFormat, string objname)
{

	switch (vertexFormat)
	{
	case PositionOnly:
		vertexShaderInfo = new VertexShaderInfo();
		fragmentShaderInfo = new FragmentShaderInfo();
		break;
	case PositionColor:
		vertexShaderInfo = new VertexShaderInfo();
		fragmentShaderInfo = new FragmentShaderInfo();
		break;
	case PositionColorNormal:
		vertexShaderInfo = new VertexShaderInfo();
		fragmentShaderInfo = new FragmentShaderInfo();
		break;
	case PositionColorTexture:
		vertexShaderInfo = new VertexShaderInfo();
		fragmentShaderInfo = new FragmentShaderInfo("..\\GraphicsPad\\Shader\\ctFragmentShaderCode.glsl");
		break;
	case PositionTexture:
		vertexShaderInfo = new VertexShaderInfo();
		fragmentShaderInfo = new FragmentShaderInfo("..\\GraphicsPad\\Shader\\tFragmentShaderCode.glsl");
		break;
	case PositionNormal:
		vertexShaderInfo = new VertexShaderInfo();
		fragmentShaderInfo = new FragmentShaderInfo();
		break;
	case PositionTextureNormal:
		vertexShaderInfo = new VertexShaderInfo();
		fragmentShaderInfo = new FragmentShaderInfo("..\\GraphicsPad\\Shader\\tFragmentShaderCode.glsl");
		break;
	case PositionColorTextureNormal:
		vertexShaderInfo = new VertexShaderInfo();
		fragmentShaderInfo = new FragmentShaderInfo("..\\GraphicsPad\\Shader\\ctFragmentShaderCode.glsl");
		break;
	}
	if (vertexShaderLocation == "")
		vertexShaderLocation = ConfigReader::Instance()->findValueForKey(objname+ "VertexShader");
	if (vertexShaderLocation != "0")
		vertexShaderInfo->shaderLocation = vertexShaderLocation.c_str();
	
	if (fragmentShaderLocation == "")
	fragmentShaderLocation = ConfigReader::Instance()->findValueForKey(objname + "FragmentShader");
	if (fragmentShaderLocation != "0")
		fragmentShaderInfo->shaderLocation = fragmentShaderLocation.c_str();
	
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
	renderinfo.setVertexShaderInfo(vertexShaderInfo);
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
	renderinfo.setVertexShaderInfo(vertexShaderInfo);
	renderinfo.setTextureInfo(new TextureInfo(renderinfo.getGeometry()->texturePath,objname));
}

void MeshComponent::setRenderInfo_Line(glm::vec3 point1, glm::vec3 point2)
{
	renderinfo.setGeometry(ShapeGenerator::makeLine(point1,point2));
	renderinfo.setTransfromInfo(new TransformInfo(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::quat()));
	makeShaderInfo(renderinfo.getGeometry()->VertexFormat, "noname");
	setUpFragmentVertexShader();
	renderinfo.setVertexShaderInfo(vertexShaderInfo);
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
	m_Layout = new QVBoxLayout;
	m_Layout->addSpacing(15);
	m_Layout->setContentsMargins(2, 0, 8, 0);

	int curProperty = 0;
	properties[curProperty] = new QHBoxLayout;
	m_Layout->addLayout(properties[curProperty]);
	properties[curProperty]->addWidget(propertyNames[curProperty] = new QLabel("Texture"));
	propertyNames[curProperty]->setFixedWidth(80);
	propertyNames[curProperty]->setContentsMargins(5, 5, 0, 5);
	QFrame* line = new QFrame();
	line->setGeometry(QRect(0, 0, 2, 30));
	line->setFrameShape(QFrame::VLine); //Replace by VLine for vertical line
	line->setFrameShadow(QFrame::Plain);
	properties[curProperty]->addWidget(line, 0, Qt::AlignLeft);
	if (renderinfo.getTextureInfo())
	{
		QPushButton* texButton = new QPushButton(renderinfo.getTextureInfo()->GetTexPath().c_str(), this);
		texButton->setObjectName("TexButton");
		properties[curProperty]->addWidget(texButton);
		connect(texButton, SIGNAL(pressed()), this, SLOT(UpdateTextureInfo()));
	}

	m_Layout->insertStretch(-1, 1);
	m_Layout->sizeHint().setHeight(50);
	m_Layout->minimumSize().setHeight(50);
	m_Layout->addSpacing(15);
	setLayout(m_Layout);
	layoutHasData = true;
	setTitle(m_name);
	layoutInitalized = true;
}

void MeshComponent::DeleteWidgets()
{

}

bool MeshComponent::Initialize()
{
	return true;
}

void MeshComponent::UpdateTextureInfo()
{
	int test = 0;
}
