#version 430

out vec3 daColor;

uniform float uMin, uMax;
uniform sampler2D myTextureSampler;
uniform vec2 tc_offset[9];

in float vLightIntensity;
in vec3 theVertexColor;
in vec2 UV;

void main()
{
    vec4 sampler[9];
    vec4 minValue = vec4(1.0);

    for (int i = 0; i < 9; i++)
    {
        sampler[i] = texture2D(myTextureSampler, UV.st + tc_offset[i]);
        minValue = min(sampler[i], minValue);
    }

	float sum = minValue.r + minValue.g + minValue.b + minValue.a;
	sum = (sum )/4;

	if(sum <= uMin )
	discard;

	if(sum >= uMax )
	discard;

    daColor = theVertexColor.rgb * vec3(1.5,1.5,1.5);
}
