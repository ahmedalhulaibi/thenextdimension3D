#version 120

// 5 varyings
varying vec2 var_texcoord;
varying vec3 var_position;

varying vec3 var_tangent;
varying vec3 var_bitangent;
varying vec3 var_normal;

// 3 uniforms
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
//uniform vec3 position;
const vec3 l = vec3(-1.0, -1.0, 0.0);
void main()
{
	vec3 normalTangent = texture2D(normalMap, var_texcoord).rgb;
	normalTangent = normalTangent*2.0 - 1.0;

	//position += l;
	//lightPos += l;
	//vec3 positionToLight = lightPos - var_position;
	//positionToLight = normalize(positionToLight);

	vec3 positionToLightTangent;
	positionToLightTangent.x = dot(normalize(var_tangent), l);
	positionToLightTangent.y = dot(normalize(var_bitangent), l);
	positionToLightTangent.z = dot(normalize(var_normal), l);

	float diffuse = dot(positionToLightTangent, normalTangent);

	vec3 colour = texture2D(diffuseMap, var_texcoord).rgb;
	gl_FragColor.rgb = colour * diffuse;
	gl_FragColor.a = 1;
}