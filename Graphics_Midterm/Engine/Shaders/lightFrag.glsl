#version 420 

in vec4 vertColor;
in vec4 vertPosition;
in vec4 vertexNormal;
out vec4 FragColor;



struct Light
{
	vec4 position;
	vec4 diffuse;
	vec4 specular;
	vec4 attenuation;
	vec4 direction;
    vec4 properties;
    bool lightOn;
};

uniform vec4 cameraView;

uniform bool doNotLight;

const int DirectionlightId = 2;
const int SpotLightId = 1;
const int PointLigthId = 0;
const int lightCount = 10;

uniform Light lightList[lightCount];



vec4 CalculateLighting(vec3 materialColor, vec3 vNormal, vec3 vPosition, vec4 vSpecular);


void main()
{

	vec4 vertexRBGA = vertColor;

	if(doNotLight)
	{
		FragColor = vertexRBGA;
		return;
	}

	// Hardcoding for midtermy thingy
	vec4 vertexSpec = vec4(1.0f,1.0f,1.0f,1.0f);

	vec4 vertexLit = CalculateLighting(vertexRBGA.rgb, vertexNormal.xyz, vertPosition.xyz, vertexSpec);

    FragColor = vertexLit;

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
		int lightType = int(lightList[index].properties.x);

		// Switch according to what light type it is

		//=============== DIRECTIONAL LIGHT ================
        
		if(lightType == DirectionlightId)
		{
			vec3 lightContrib = lightList[index].diffuse.rgb;

			float dotProduct = dot(- lightList[index].direction.xyz, normalize(normal.xyz));

			dotProduct = max(0.0f, dotProduct);

			lightContrib *= dotProduct;

			finalColor.rgb += (materialColor.rgb * lightList[index].diffuse.rgb * lightContrib);

			return finalColor;
		}

		// Assuming its a point light

		
			vec3 lightVector = lightList[index].position.xyz - vPosition.xyz;
			float distancefromLight = length(lightVector);

			lightVector = normalize(lightVector);

			float dotProduct = dot(lightVector, vNormal.xyz); 
			dotProduct = max(0.0f, dotProduct); 

			vec3 lightDiffuse = (dotProduct * lightList[index].diffuse.rgb);


			vec3 lightSpecular = vec3(0.1f);
			vec3 reflectVector = reflect(-lightVector,normalize(normal.xyz));

			vec3 eyeVector = normalize(cameraView.xyz - vPosition.xyz);

			float objectSpecPower = vSpecular.w;

			lightSpecular = pow(max(0.0f, dot(eyeVector,reflectVector)),objectSpecPower) * lightList[index].specular.rgb;

			float finalAttenuation =  1.0f / 
			( lightList[index].attenuation.x + 
			lightList[index].attenuation.y * distancefromLight + 
			lightList[index].attenuation.z * distancefromLight * distancefromLight);
			
			lightDiffuse *=  finalAttenuation;
			lightSpecular *= finalAttenuation;

			
			
	

		if(lightType == SpotLightId)
		{
			lightVector = lightList[index].position.xyz - vPosition.xyz;

			lightVector = normalize(lightVector);

			float currentRayAngle = dot(lightVector.xyz, lightList[index].direction.xyz);

			currentRayAngle = max(0.0f, currentRayAngle);


			float outerConeAngleCosine = cos(radians(lightList[index].properties.z));
		    float innerConeAngleCosine = cos(radians(lightList[index].properties.y));
		

			if(currentRayAngle < outerConeAngleCosine)
			{
				lightDiffuse = vec3(0.0f,0.0f,0.0f);
				lightSpecular = vec3(0.0f,0.0f,0.0f);
			}
			else if(currentRayAngle < innerConeAngleCosine)
			{
				float penumbraRatio = (currentRayAngle - outerConeAngleCosine) / (innerConeAngleCosine - outerConeAngleCosine);

				lightDiffuse *= penumbraRatio;
				lightSpecular *=penumbraRatio;
			}

		}



		finalColor.rgb += (materialColor.rgb*lightDiffuse.rgb) + (vSpecular.rgb* lightSpecular.rgb);
		
	}


	finalColor.a = 1.0f;

	return finalColor;
}