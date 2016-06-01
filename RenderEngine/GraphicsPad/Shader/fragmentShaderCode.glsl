#version 430

layout(location = 0) out vec3 daColor;
in vec3 theVertexColor;
in vec2 UV;

uniform bool discardBasedOfDepth;
uniform bool regularDepth;

uniform sampler2D renderedTexture;
uniform sampler2D depthTexture;
 
vec3 depth(){
    float v = pow(texture(depthTexture, UV).r , 512);
	return vec3(v,v,v);
}

void main()
{
	//daColor = texture2D(renderedTexture, UV).rgb;
	if(discardBasedOfDepth)
	{
		vec3 color = depth();
		if(color.r + color.b + color.g >2.0)
		discard;
		daColor = (texture2D(renderedTexture, UV).rgb * 2 + color)/3;
	}
	else if(regularDepth)
	{
		daColor = depth();
	}
	else
	{
		daColor =texture2D(renderedTexture, UV).rgb;
	}
};