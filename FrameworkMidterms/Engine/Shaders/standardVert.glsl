// VCustom  Basic Vertex Shader
#version 420 


uniform mat4 viewProjMat;
uniform mat4 parentModel;
uniform mat4 invModel;

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec3 vNormal;

out VertexShaderOut
{
	vec4 outWorldPosition;
	//vec4 outWorldNormal;
	//vec4 outVertexColor;

} vertOut;

void main()
{
	vec4 modelPosition = parentModel * vec4(vPosition , 1.0f);



	vec4 calculatedNormal = invModel * vec4(vNormal , 1.0f);


	vertOut.outWorldPosition = modelPosition;
  //  vertOut.outWorldNormal.xyz = normalize(calculatedNormal.xyz);
  //vertOut.outWorldNormal.w = 1.0f;

	

	vertOut.outVertexColor = vColor;
	
	gl_Position = viewProjMat * modelPosition;
}