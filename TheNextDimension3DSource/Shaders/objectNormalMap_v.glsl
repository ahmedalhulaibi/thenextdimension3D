#version 120

// 2 varyings
varying vec2 var_texcoord;
varying vec3 var_position;
varying vec3 eyePos;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	vec4 eyePosition = gl_ModelViewMatrix * gl_Vertex;
	eyePos = eyePosition.xyz;
	var_position = gl_Vertex.xyz;
	var_texcoord = gl_MultiTexCoord0.st;
}