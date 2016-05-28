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

out float vLightIntensity;
out vec3 theVertexColor;
out vec2 UV;

void main()
{
	vec4 vertex = aVertex;
	if(aVertex.x > 0)
	{
		vertex.x = .5;
	}
	else vertex.x = -.5;
	if(aVertex.y > 0)
	{
		vertex.y = .5;
	}
	else vertex.y = -.5;
	if(aVertex.z > 0)
	{
		vertex.z = .5;
	}
	else vertex.z = -.5;

	vec3 lightVector = normalize(uLightPosition - aVertex.xyz);
	vLightIntensity = 0;

	gl_Position = uModelViewProjectionMatrix * vertex;
	theVertexColor = aColor.rgb;
	UV = texture;
};