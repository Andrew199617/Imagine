#version 430

out vec3 daColor;
in vec3 theVertexColor;
in vec2 UV;

uniform sampler2D myTextureSampler;
 
void main()
{
	daColor = texture2D(myTextureSampler, UV).rgb;
};