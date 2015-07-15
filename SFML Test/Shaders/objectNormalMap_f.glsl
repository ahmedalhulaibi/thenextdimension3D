#version 120

// 2 varyings
varying vec2 var_texcoord;
varying vec3 var_position;
varying vec3 eyePos;

// 2 uniforms
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
//uniform vec3 position;
const vec3 l = vec3(0.2, 0.5, 0.5);
//const vec3 h = vec3(0.1, 0.3, 0.3);
const vec3 ambientColour = vec3(0.07,0.07,0.07);

void main()
{
	vec3 normal = texture2D(normalMap, var_texcoord).rgb;
	normal = normal*2.0 - 1.0; // convert from (0,1) range to (-1,1) range

	//lightPos = position + l;
	//vec3 positionToLight = lightPos - var_position;
	//vec3 positionToLight = normalize(positionToLight);
	float diffuse = max(0.0, dot(normal, l));
	vec3 diffuseColour = diffuse * vec3(0.7);

	float shininess = 5.0;

	vec3 v = -normalize(eyePos);
	vec3 h = normalize(v+l);

	//specular
	float specular = pow(max(dot(normal, h), 0.0), shininess);
	vec3 specularColour = specular * vec3(0.7);

	if(diffuse <= 0)
	{
		specular = 0;
	}

	vec3 colour = texture2D(diffuseMap, var_texcoord).rgb;
	gl_FragColor.rgb = (colour * (diffuseColour + specularColour)) + ambientColour;
	gl_FragColor.a = 1;
}