#version 430

out vec3 daColor;

const float PI = 3.14159265;

in float vLightIntensity;
in vec3 theVertexColor;
in vec2 UV;

uniform float uD;
uniform float uR;

uniform sampler2D myTextureSampler;
uniform sampler2D bumpMap;

void main( )
{
	ivec2 ires = textureSize( myTextureSampler, 0 );
	float Res = float( ires.s ); // assume it’s a square
	// texture image
	vec2 st = UV;
	float Radius = Res * uR;
	vec2 xy = Res * st; // pixel coordinates from
	// texture coords
	vec2 TwirlOrigin = xy - Res/2.; 
	float r = length( TwirlOrigin );
	float beta = atan(TwirlOrigin.y,TwirlOrigin.x) + radians(uD) * (Radius-r)/Radius;
	vec2 xy1 = xy;
	if (r <= Radius)
	{
		xy1 = Res/2. + r * vec2( cos(beta), sin(beta) );
	}
	st = xy1/Res; // restore coordinates
	vec3 irgb = texture( myTextureSampler, st ).rgb;
	daColor = irgb;
}
	