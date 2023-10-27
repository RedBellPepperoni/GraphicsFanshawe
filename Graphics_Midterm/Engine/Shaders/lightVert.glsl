// VCustom  Basic Vertex Shader
#version 420 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec3 vNormal;



out vec4 vertColor;
out vec4 vertPosition;

uniform mat4 model;
uniform mat4 modelInv;
uniform mat4 viewProj;

uniform vec4 matColor;



bool doNotLight;

struct LightProperites
{
	vec4 position;
	vec4 color;
	vec4 specular;
	vec4 direction;
    vec4 spotProperties
    bool lightOn;
}

const int DirectionlightId = 2;
const int SpotLightId = 1;
const int PointLigthId = 0;
const int lightCount = 10;

uniform Light allLights[lightCount];


vec4 CalculateLighting(vec3 materialColor, vec3 vNormal, vec3 vPosition, vec4 vSpecular);

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



vec4 CalculateLighting(vec3 materialColor, vec3 vNormal, vec3 vPosition, vec4 vSpecular)
{
	vec3 normal = normalize(vNormal)
}