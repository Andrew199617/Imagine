#version 430

in layout(location=0) vec4 aVertex;
in layout(location=1) vec3 aColor;
in layout(location=2) vec2 texture;
in layout(location=3) vec3 aNormal;

uniform mat4 uModelViewProjectionMatrix;

out vec3 theVertexColor;
out vec2 UV;

void main()
{

	gl_Position = uModelViewProjectionMatrix * aVertex; 
	theVertexColor = vec3(1,1,1);
	UV = texture;
};