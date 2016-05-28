#version 430

out vec3 daColor;

in float vLightIntensity;
in vec3 theVertexColor;
in vec2 UV;

uniform sampler2D myTextureSampler;
uniform sampler2D bumpMap;
uniform bool isBumped;

void main()
{	
	vec3 normal = normalize(texture2D(bumpMap, UV).rgb * 2.0 - 1.0);

	vec3 light_pos = normalize(vec3(1.0, 1.0, 1.5));

	float diffuse = max(dot(normal, light_pos), 0.0);  
  
	vec3 color = diffuse * texture2D(myTextureSampler, UV).rgb;  

	// Set the output color of our current pixel  
	if(isBumped)
		daColor = color; 
	else
		daColor = texture2D(myTextureSampler, UV).rgb;
	
}
	