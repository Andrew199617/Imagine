#pragma once
#include "glm.hpp"

struct vPosition
{
	glm::vec3 position;
};

struct vPositionColor
{
	glm::vec3 position;
	glm::vec3 color;
};

struct vPositionTexture
{
	glm::vec3 position;
	glm::vec2 texture;
};

struct vPositionNormal
{
	glm::vec3 position;
	glm::vec3 normal;
};

struct vPositionColorTexture
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texture;
};

struct vPositionColorNormal
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
};

struct vPositionTextureNormal
{
	glm::vec3 position;
	glm::vec2 texture;
	glm::vec3 normal;
};

struct vPositionColorTextureNormal
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texture;
	glm::vec3 normal;
};