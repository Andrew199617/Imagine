#version 430

out vec3 daColor;
in float vLightIntensity;
in vec3 theVertexColor;
in vec2 UV;

uniform sampler2D myTextureSampler;
uniform vec3 objectColor;

void main()
{	
	
	vec4 diffuseLight = vec4(vLightIntensity,vLightIntensity,vLightIntensity,1.0f);
	vec4 diffuse = diffuseLight * vec4(1,1,1 , 1.0f);

	vec3 tex = texture( myTextureSampler, UV ).rgb;
	//vec4 daColor1 = (vec4(1.0,1.0,1.0,1.0f) + clamp(diffuse, 0, 1)) * ((theVertexColor));
	vec3 daColor1 = (theVertexColor + vec3(.6,.6,.6)) / 2;
	daColor = objectColor.xyz;
};
	