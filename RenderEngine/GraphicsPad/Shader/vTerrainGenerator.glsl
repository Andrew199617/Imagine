#version 430

in layout(location=0) vec4 aVertex;
in layout(location=1) vec3 aColor;
in layout(location=2) vec2 texture;
in layout(location=3) vec3 aNormal;

uniform mat4 uModelViewMatrix;
uniform mat4 uModelViewProjectionMatrix;
uniform mat3 uNormalMatrix;
uniform mat4 uProjectionMatrix;

uniform vec3 uLightPosition;
uniform float frequency;

out float vLightIntensity;
out vec3 theVertexColor;
out vec2 UV;

uniform sampler2D bumpMap;

void main()
{
	vec3 lightVector = normalize(uLightPosition - aVertex.xyz);
	vLightIntensity = dot(lightVector,normalize(vec3(uProjectionMatrix * vec4(aNormal,0))));

	vec4 vertex = aVertex;

	vec4 color = texture2D(bumpMap, texture);
	//float height = 1.0f;  
	float sum = color.r + color.b + color.g;

	vertex.y = sum * 1/frequency;

	gl_Position = uModelViewProjectionMatrix * vertex;
	theVertexColor = aColor.rgb;
	UV = texture;
};