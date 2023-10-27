#version 420 

in vec4 vertColor;
in vec4 vertPosition;
in vec4 vertexNormal;
out vec4 FragColor;



uniform vec3 cameraView;

uniform bool doNotLight;

const int DirectionlightId = 2;
const int SpotLightId = 1;
const int PointLigthId = 0;
const int lightCount = 10;


struct DirLight
{
	vec3 position;
	vec3 color;
	vec3 intensity;
	vec3 specular;

};



struct PointLight
{
	vec3 position;
	vec3 color;
	vec3 intensity;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

};




uniform DirLight dirLight;

#define MAX_POINT_LIGHTS 6
uniform PointLight pointLightList[MAX_POINT_LIGHTS];


vec3 CalculateDirectionalLight(vec4 vPos, vec4 vNormal, DirLight light);
vec3 CalculatePointLight(vec4 vPos, vec4 vNormal, PointLight light);


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



vec3 CalculateDirectionalLight(vec4 vPos ,vec4 vNormal,  DirLight light)
{
	vec3 lightPos = light.position;
	vec3 lightColor = light.color;


    vec3 ambient = light.intensity * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(vNormal.xyz);
    vec3 lightDir = normalize(lightPos - vPos.xyz);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
   
    vec3 viewDir = normalize(cameraView - vPos.xyz);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular);

	return result;

}

vec3 CalculatePointLight(vec4 vPos, vec4 vNormal, PointLight light)
{
	vec3 result = vec3(0.0f,0.0f,0.0f);

	return result;
}


vec4 CalculateLighting(vec4 vPos, vec4 vColor, vec4 vNormal)
{
	vec4 finalColor = vec4((CalculateDirectionalLight(vPos,vNormal,dirLight) * vColor.xyz),1.0f);	
	

	
	finalColor.a = 1.0f;

	return finalColor;
}