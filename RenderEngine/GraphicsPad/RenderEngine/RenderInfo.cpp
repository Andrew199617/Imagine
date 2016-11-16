#include "RenderInfo.h"
#pragma warning(push)
#pragma warning (disable:4127)
#pragma warning (disable:4201)
#include "TransformInfo.h"
#pragma warning(pop)
#include "Geometry.h"
#include "VertexShaderInfo.h"
#include <gl\glew.h>
#include "TextureInfo.h"
#include "..\VertexFormats.h"
#include "..\Vertex.h"
#include "gtx\transform.hpp"

RenderInfo::RenderInfo(RenderInfo* me, RenderInfo* next)
{
	this->m_mesh = me->m_mesh;
	this->m_transformInfo = me->m_transformInfo;
	this->m_vertexShaderInfo = me->m_vertexShaderInfo;
	this->m_textureInfo = me->m_textureInfo;
	this->m_fragmentShaderInfo = me->m_fragmentShaderInfo;
	Next(next);
	isEnabled = true;
}

void RenderInfo::Draw(float dt, bool isPlaying)
{
	if (!isEnabled)
	{
		if (next != 0)
		{
			next->Draw(dt,isPlaying);
		}
		return;
	}
	
	m_vertexShaderInfo->useProgram();

	glBindBuffer(GL_ARRAY_BUFFER, m_mesh->m_vertexId);
	SendAttributeData();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh->m_indexId);
	SendUniformData(dt,isPlaying);

	if (m_mesh->VertexFormat & HasTexture)
	{
		m_textureInfo->bindTexture();
	}

	glDrawElements(GL_TRIANGLES, m_mesh->m_indexCount, GL_UNSIGNED_INT, (void*)m_mesh->m_indexByteOffset);

	if (m_mesh->VertexFormat & HasTexture)
	{
		m_textureInfo->unBindTexture();
	}

	if (next != 0)
	{
		next->Draw(dt,isPlaying);
	}
	
}

void RenderInfo::SendAttributeData()
{
	
	int VERTEX_BYTE_SIZE = m_mesh->m_vertexStride;
	switch (m_mesh->VertexFormat)
	{
	case PositionOnly:
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset));
		break;
	case PositionColor:
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset + sizeof(float) * 3));
		break;
	case PositionColorNormal:
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset + sizeof(float) * 3));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset + sizeof(float) * 6));
		break;
	case PositionColorTexture:
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset + sizeof(float) * 3));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset + sizeof(float) * 6));
		break;
	case PositionTexture:
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset + sizeof(float) * 3));
		break;
	case PositionNormal:
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset + sizeof(float) * 3));
		break;
	case PositionTextureNormal:
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset + sizeof(float) * 3));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset + sizeof(float) * 5));
		break;
	case PositionColorTextureNormal:
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset + sizeof(float) * 3));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset + sizeof(float) * 6));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(m_mesh->m_vertexByteOffset + sizeof(float) * 8));
		break;
	}
}

void RenderInfo::SendUniformData(float, bool isPlaying)
{
	glm::mat4 mat;
	if (m_mesh->centerOfMass)
	{
		glm::mat4 COM = glm::translate(glm::vec3(m_transformInfo->m_translateTransform[3][0], m_transformInfo->m_translateTransform[3][1], m_transformInfo->m_translateTransform[3][2]) - *m_mesh->centerOfMass);
		mat = COM * m_transformInfo->m_rotateTransform * m_transformInfo->m_scaleTransform;
	}
	else
	{
		mat = m_transformInfo->m_translateTransform * m_transformInfo->m_rotateTransform * m_transformInfo->m_scaleTransform;
	}

	if (m_mesh->m_animationInfo.hasAnimation && isPlaying)
	{
		mat *= m_mesh->m_animationInfo.animationData[m_mesh->m_animationInfo.currentFrame];
		m_mesh->m_animationInfo.IncrementCurrentFrame();
	}
	else if (m_mesh->m_animationInfo.hasAnimation)
	{
		mat *= m_mesh->m_animationInfo.animationData[m_mesh->m_animationInfo.currentFrame];
	}
	glm::mat4 ModelViewProjectionMatrix = TransformInfo::projectionMatrix * TransformInfo::WorldToViewMatrix * mat;
	m_transformInfo->ModelViewProjectionMatrix = mat;
	glm::mat4 ModelViewMatrix = TransformInfo::WorldToViewMatrix * mat;
	glm::mat4 NormalMatrix = glm::transpose(glm::inverse(TransformInfo::WorldToViewMatrix));

	glUniformMatrix4fv(m_vertexShaderInfo->uNormalMatrixUL, 1, GL_FALSE, &NormalMatrix[0][0]);
	glUniformMatrix4fv(m_vertexShaderInfo->uModelViewProjectionMatrixUL, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(m_vertexShaderInfo->uModelViewMatrixUL, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix4fv(m_vertexShaderInfo->uProjectionMatrixUL, 1, GL_FALSE, &mat[0][0]);

	glUniform3fv(m_vertexShaderInfo->uObjectColor, 1, &color[0]);
	glUniform1fv(m_vertexShaderInfo->uMaxUL, 1, &VertexShaderInfo::uMax);
	glUniform1fv(m_vertexShaderInfo->uMinUL, 1, &VertexShaderInfo::uMin);
	glUniform1i(m_vertexShaderInfo->uIsBumpedUL, m_textureInfo->IsBumped());
	glUniform3fv(m_vertexShaderInfo->uLightPositionUL, 1, &VertexShaderInfo::lightPosition[0]);
	glUniform1fv(m_vertexShaderInfo->uPercentLerped, 1, &VertexShaderInfo::percentLerped);
	glUniform1fv(m_vertexShaderInfo->percentRippledUniformLocaton, 1, &m_vertexShaderInfo->percentRippled);
	glUniform1fv(m_vertexShaderInfo->densityUniformLocation, 1, &m_vertexShaderInfo->density);
	glUniform1fv(m_vertexShaderInfo->frequencyUniformLocation, 1, &m_vertexShaderInfo->uR);
	glUniform1fv(m_vertexShaderInfo->uDUniformLocation, 1, &m_vertexShaderInfo->uD);

}
