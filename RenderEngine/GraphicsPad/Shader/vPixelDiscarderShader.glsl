#version 430

uniform mat4 uModelViewMatrix;
uniform mat4 uModelViewProjectionMatrix;
uniform mat3 uNormalMatrix;
uniform mat4 uProjectionMatrix;

in layout(location=0) vec4 aVertex;
in layout(location=1) vec3 aColor;
in layout(location=2) vec2 texture;
in layout(location=3) vec3 aNormal;

out vec3 vColor;
out vec2 vST;

void main()
{
	vST = texture;
	vColor = aColor;
	gl_Position = uModelViewProjectionMatrix * aVertex;
};