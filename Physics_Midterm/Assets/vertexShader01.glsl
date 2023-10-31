// Vertex shader
#version 420

uniform mat4 MVP;

in vec3 vCol;		// was 'attribute' from vertex buffer
in vec3 vPos;

out vec3 color;

void main()
{
	gl_Position = MVP * vec4(vPos, 1.0);
	
	
	color = vCol;
}
