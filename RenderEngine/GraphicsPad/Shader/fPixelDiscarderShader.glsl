#version 430

uniform float density;
uniform float frequency;

in vec3 vColor;
in float vLightIntensity;
in vec2 vST;

const vec3 color = vec3(.5f,.5f,0.0f);

out vec3 daColor;

void main()
{
	float sf = vST.s * frequency;
	float tf = vST.t * frequency;
	if( fract( sf ) >= density && fract( tf ) >= density )
	discard;
	daColor = vec3(vColor.rgb);	
};