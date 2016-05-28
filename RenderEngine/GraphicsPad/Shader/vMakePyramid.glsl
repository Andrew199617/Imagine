#version 430

in layout(location=0) vec4 aVertex;
in layout(location=1) vec3 aColor;
in layout(location=2) vec2 texture;
in layout(location=3) vec3 aNormal;

uniform mat4 uModelViewMatrix;
uniform mat4 uModelViewProjectionMatrix;
uniform mat3 uNormalMatrix;
uniform mat4 uProjectionMatrix;

uniform float uPercentLerped;
uniform vec3 uLightPosition;

out float vLightIntensity;
out vec3 theVertexColor;
out vec2 UV;

void main()
{
	vec4 vertex = aVertex;
	if(aVertex.x > 0)
	{
		vertex.x = mix(aVertex.x,2,uPercentLerped);
	}
	else vertex.x = mix(aVertex.x,-2,uPercentLerped);
	if(aVertex.z > 0)
	{
		vertex.z = mix(aVertex.z,2,uPercentLerped);
	}
	else vertex.z = mix(aVertex.z,-2,uPercentLerped);
	if(aVertex.y > 0)
	{
		vertex = mix(aVertex,vec4(0,2,0,1),uPercentLerped);
	}
	else vertex.y = mix(aVertex.y,-2,uPercentLerped);

	vec3 lightVector = normalize(uLightPosition - aVertex.xyz);
	vLightIntensity = dot(lightVector,normalize(vec3(uProjectionMatrix * vec4(aNormal,0))));

	gl_Position = uModelViewProjectionMatrix * vertex;
	theVertexColor = aColor.rgb;
	UV = texture;
};