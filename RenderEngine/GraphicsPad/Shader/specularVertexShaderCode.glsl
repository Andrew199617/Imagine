#version 430

in layout(location=0) vec4 aVertex;
in layout(location=1) vec3 aColor;
in layout(location=2) vec2 texture;
in layout(location=3) vec3 aNormal;

uniform mat4 uModelViewProjectionMatrix;
uniform mat4 modelToWorldTransformMatrix;

out vec3 theNormal;
out vec3 thePosition;
out vec3 theVertexColor;

void main()
{
	gl_Position = uModelViewProjectionMatrix * aVertex;
	theNormal = normalize(vec3(modelToWorldTransformMatrix * vec4(aNormal,0)));
	thePosition = vec3(modelToWorldTransformMatrix * aVertex);
	theVertexColor = aColor;
};