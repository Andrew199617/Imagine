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
	vec3 lightVector = normalize(uLightPosition - aVertex.xyz);
	vLightIntensity = dot(lightVector,normalize(vec3(uProjectionMatrix * vec4(aNormal,0))));
	//vLightIntensity = vec4(brightness,brightness,brightness,1.0f);

	gl_Position = uModelViewProjectionMatrix * aVertex; 
	theVertexColor = aColor.rgb;
	UV = texture;
};