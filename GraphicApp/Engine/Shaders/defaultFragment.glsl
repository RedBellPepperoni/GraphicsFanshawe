// Fragment shader
#version 420

in VertexShaderOut
{
	vec4 outWorldPosition;
	vec4 outWorldNormal;
	vec4 outVertexColor;
	
} fragmentIn;

layout(location = 0) out vec4 outDiffuse;


void main()
{
   outDiffuse = fragmentIn.outVertexColor;
}