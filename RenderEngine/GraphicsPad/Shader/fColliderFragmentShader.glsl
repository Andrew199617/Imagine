#version 430

layout(location = 0) out vec3 daColor;

in vec3 theVertexColor;
in vec2 UV;

uniform vec3 objectColor;

float density = .3f;
float frequency = 50.0f;
 
void main()
{
	float sf = UV.s * frequency;
	float tf = UV.t * frequency;
	if( fract( sf ) >= density && fract( tf ) >= density )
	discard;
	daColor = objectColor.rgb;	
};