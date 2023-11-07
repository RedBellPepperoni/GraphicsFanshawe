// VCustom  Basic Vertex Shader
#version 420 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 vColor;
 
//layout (location = 2) in vec3 vNormal;

out vec4 vertColor;
out vec4 vertPosition;

uniform mat4 model;
uniform mat4 modelInv;
uniform mat4 viewProj;

uniform vec4 matColor;

void main()
{
	
	mat4 modelViewProj = viewProj * model;
	gl_Position = modelViewProj * vec4(vPosition, 1.0f);

	vertColor = vColor;

	if (matColor != vec4 ( 0.0f, 0.0f, 0.0f, 1.0f) )
	{		
		vertColor = matColor;
	}

	vertPosition = model * vec4(vPosition, 1.0f);
	
	
	

}