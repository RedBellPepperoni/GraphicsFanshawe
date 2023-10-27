#version 420 

in vec4 vertColor;
in vec4 vertPosition;
in vec4 vertexNormal;
out vec4 FragColor;



struct Light
{
	vec4 position;
	vec4 color;
	vec4 specular;
	vec4 attenuation;
	vec4 direction;
    vec4 properties;
    bool lightOn;
};

uniform vec3 cameraView;

uniform bool doNotLight;

const int DirectionlightId = 2;
const int SpotLightId = 1;
const int PointLigthId = 0;
const int lightCount = 10;

uniform Light lightList[lightCount];

vec4 CalculateDirectionalLight(vec4 vPos, vec4 vColor,vec4 vNormal, Light dirlight);

vec4 CalculateLighting(vec4 vPos, vec4 vColor, vec4 vNormal);


void main()
{

	

	if(doNotLight)
	{
		FragColor = vertColor;
		return;
	}


	vec4 vertexLit = CalculateLighting(vertPosition, vertColor, vertexNormal);


    FragColor.xyz = vertexLit.xyz;
	FragColor.a = 1.0f;

}



vec4 CalculateDirectionalLight(vec4 vPos, vec4 vColor,vec4 vNormal, Light dirlight)
{
	vec3 lightPos = dirlight.position.xyz;
	vec3 lightColor = dirlight.color.rgb;

	// ambient
    float ambientStrength = 0.4f;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(vNormal.xyz);
    vec3 lightDir = normalize(lightPos - vPos.xyz);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraView - vPos.xyz);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular) * vColor.rgb;

	return vec4(result , 1.0f);
}

vec4 CalculateLighting(vec4 vPos, vec4 vColor, vec4 vNormal)
{
	vec4 finalColor = vec4(1.0f,1.0f,1.0f,1.0f);



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
			finalColor = CalculateDirectionalLight(vPos,vColor,vNormal,lightList[index]);		
		}

		
	}


	finalColor.a = 1.0f;

	return finalColor;
}