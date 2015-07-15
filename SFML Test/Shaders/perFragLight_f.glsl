#version 120

struct SpotLight
{
	vec3 position; 
	//vec3 direction;
	vec3 color;

	//float cutOff;
	//float cosInnerCone;
	//float cosOuterCone;

	//float constantAttenuation;
	//float linearAttenuation;
	//float quadraticAttenuation;
};



varying vec4 eye;
varying vec3 normal;
varying vec4 pos;
const float shininess = 2.0;
const float rim = 10.0;
uniform SpotLight lights[5];
uniform int useTexture;
uniform int useRim;
uniform int showSpec;

uniform sampler2D image;

vec3 returnTotalLight(SpotLight light)
{
	vec3 P = pos.xyz;//vertex positon
	vec3 N = normalize(normal);//eye position in camera space
	vec3 V = normalize(eye.xyz - P);//view direction
	vec3 L = normalize(light.position - P);//light direction
	vec3 H = normalize(L + V);//half vec for spec term

	float fresnelTerm = 1.0 - dot(V,-L);
	fresnelTerm = pow(fresnelTerm,rim);

	float specularLight = pow(max(dot(N,H),0), shininess);
	vec3 fresnel = vec3(0.0);
	if(useRim == 1) 
	{
		fresnel = light.color * specularLight * fresnelTerm;
	}
	
	
	float diffuseLight = max(dot(N,L),0);
	vec3 diffuse = vec3(light.color *diffuseLight);

	if(diffuseLight<=0)
	{
		specularLight = 0;
	}

	vec3 specular =vec3( light.color * specularLight);

	if(showSpec == 1)
	{
		return /*specular + */fresnel;
	}

	return vec3(specular + diffuse + fresnel);
};
 
void main() 
{
	vec3 color = texture2D(image, gl_TexCoord[0].st).rgb;
	vec3 totalLight = vec3(0.0);
	for(int i = 0; i < 5; i++)
	{
		totalLight += returnTotalLight(lights[i]);
	}
	gl_FragColor.rgb = (totalLight);
	if(useTexture == 1)
	{
		gl_FragColor.rgb = (color * totalLight);
	}
}