#version 430

out vec4 daColor;
in vec3 theNormal;
in vec3 thePosition;
in vec3 theVertexColor;

uniform vec3 eyePositionWorld;
uniform vec3 ambientLight;
uniform vec3 lightPosition;
uniform vec3 diffuseColor;
uniform vec3 dom;
uniform vec3 SpecularColor;
uniform int exponent;
uniform sampler2D myTextureSampler;

void main()
{
	
	//Diffuse
	vec3 lightVector = normalize(lightPosition - thePosition);
	float brightness = dot(lightVector,normalize(theNormal));
	vec4 diffuseLight = vec4(brightness,brightness,brightness,1.0f);

	//specular
	vec3 reflectedLightVectorWorld = reflect(-lightVector, theNormal);
	vec3 eyeVectorWorld = normalize(eyePositionWorld - thePosition);
	float s = dot(reflectedLightVectorWorld,eyeVectorWorld);
	s = pow(s,exponent);
	vec4 specularLight = vec4(s * (SpecularColor.x),s* (SpecularColor.y),s* (SpecularColor.z),1);
	vec4 diffuse = diffuseLight * vec4(diffuseColor , 1.0f);
	daColor = (vec4(ambientLight,1.0f) + clamp(diffuse, 0, 1)) * vec4(theVertexColor,1.0f) + clamp(specularLight,0,1);

};	