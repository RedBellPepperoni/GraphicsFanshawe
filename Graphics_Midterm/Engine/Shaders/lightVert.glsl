// VCustom  Basic Vertex Shader
#version 420 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec3 vNormal;



out vec4 vertColor;
out vec4 vertPosition;

uniform mat4 model;
uniform mat4 viewProj;
uniform mat4 normalmatrix;

uniform vec4 matColor;



bool doNotLight;

struct LightProperites
{
	vec4 position;
	vec4 color;
	vec4 specular;
	vec4 direction;
    vec4 params
    bool lightOn;
}

const int DirectionlightId = 2;
const int SpotLightId = 1;
const int PointLigthId = 0;
const int lightCount = 10;

uniform Light lightList[lightCount];


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
	vec3 normal = normalize(vNormal);
	vec4 finalColor = vec4( 0.0f, 0.0f, 0.0f, 1.0f);


	for( int index = 0; index < lightCount; index++ )
	{
		if(lightList[index].lightOn == false)
		{
			// Skip the calculations
			continue;
		}

		//Gather each light's Type
		int lightType = int(lightList[index].params.x);

		// Switch according to what light type it is

		//=============== DIRECTIONAL LIGHT ================
        
		if(lightType == DirectionlightId)
		{
			vec3 lightContrib = lightList[index].diffuse.rgb;

			float dotPorduct = dot(= lightList[index].direction.xyz, normalize(normal.xyz));

			dotPorduct = max(0.0f, dotPorduct);

			lightContrib += dorProduct;

		}

	}
}