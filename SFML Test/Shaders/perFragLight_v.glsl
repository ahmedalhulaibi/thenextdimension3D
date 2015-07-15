#version 120
 
//struct SpotLight
//{
//	vec3 position; 
//	vec3 direction;
//	vec4 color;

//	float cutOff;
//	//float cosInnerCone;
//	//float cosOuterCone;

//	//float constantAttenuation;
//	//float linearAttenuation;
//	//float quadraticAttenuation;
//}

//varying SpotLight light;
varying vec4 eye;
varying vec4 pos;
varying vec3 normal;
//, lightDir;

//uniform spotLight lightV;
 
void main () {
 
	//light = lightV;
	//material = materialV;

	eye = gl_ModelViewMatrix * gl_Vertex;
	//lightDir = vec3(light.position - eye);
	normal = normalize(gl_NormalMatrix * gl_Normal);
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
    pos = gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; 
	gl_FrontColor = gl_Color;
}