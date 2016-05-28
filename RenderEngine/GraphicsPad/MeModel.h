#pragma once
#include <glm.hpp>

struct MeModel
{
	glm::vec3 lightPosition;
	glm::vec3 objectColors;
	glm::vec3 ambientLight;
	glm::vec3 diffuseColor;
	glm::vec3 SpecularColor;
	float uD;
	float uR;
	int exponent;
	bool resendData;
};