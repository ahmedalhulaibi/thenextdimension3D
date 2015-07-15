#version 120

// 5 varyings
varying vec2 var_texcoord;
varying vec3 var_position;

varying vec3 var_tangent;
varying vec3 var_bitangent;
varying vec3 var_normal;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	var_position = gl_Vertex.xyz;
	var_texcoord = gl_MultiTexCoord0.st;
	var_normal = gl_Normal;

	vec3 t;
	vec3 c1 = cross(var_normal, vec3(0.0, 0.0, 1.0)); 
	vec3 c2 = cross(var_normal, vec3(0.0, 1.0, 0.0)); 
	if (length(c1) > length(c2))
	{
		t = c1;
	}
	else
	{
		t = c2;
	}

	var_tangent = t;
	var_bitangent = cross(var_tangent, var_normal);
}