#version 430

in layout(location=0) vec4 aVertex;
in layout(location=1) vec3 aColor;
in layout(location=2) vec2 texture;
in layout(location=3) vec3 aNormal;

uniform mat4 uModelViewMatrix;
uniform mat4 uModelViewProjectionMatrix;
uniform float percentRippled;
uniform float numRippled;

out float vLightIntensity;
out vec3 theVertexColor;

const vec3 LIGHTPOS = vec3( 0.0, 10.0, 0.0 );
const vec3 THEVERTEXCOLOR = vec3( 0.5, 0.5, 0.0 );

out vec2 UV;

void main()
{
	vec4 thisPos = aVertex;
	theVertexColor = THEVERTEXCOLOR.rgb;

	vec2 thisXY = thisPos.xy * numRippled;
	thisPos.z = percentRippled * sin( dot( thisXY, thisXY ) );

	// now compute the normal and the light intensity
	vec3 xtangent = vec3( 1., 0., 0. );
	vec3 ytangent = vec3( 0., 1., 0. );
	xtangent.z = 2. * percentRippled * thisPos.x * cos( dot( thisXY, thisXY ) );
	ytangent.z = 2. * percentRippled * thisPos.y * cos( dot( thisXY, thisXY ) );
	vec3 thisNormal = normalize( cross( xtangent, ytangent ) );
	
	vec3 ECpos = vec3( uModelViewMatrix * thisPos );
	vLightIntensity = dot( normalize(LIGHTPOS - ECpos),
	thisNormal );
	vLightIntensity = 0.3 + abs( vLightIntensity ); // 0.3 ambient
	vLightIntensity = clamp( vLightIntensity, 0., 1. );
	
	gl_Position = uModelViewProjectionMatrix * thisPos;

	//UV = texture;
};

