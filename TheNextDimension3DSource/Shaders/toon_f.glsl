/*
	Toon fragment shader

	Computes directional lighting and uses this to output 
	CEL-SHADING.

	Also outputs normals for the next pass.
*/


#version 120


// 2 varyings
varying vec2 texcoord;
varying vec3 normal;

// 2 uniforms
uniform sampler2D inputImage;
uniform sampler2D qmap;//qmap/ramp

// 1 constant
const vec3 lightEyeDir = vec3(0.0,0.0,1.0);

void main()
{

	vec3 n = normalize(normal);

	//diffuse is q-map/ramp input
	float diffuse = max(0.0, dot(n, lightEyeDir));//diffuse coefficient

	//new lighting coefficient
	float toonBlock = texture2D(qmap, vec2(diffuse,0.5)).r;//since its a grayscale we can use a float for this

	vec3 c = texture2D(inputImage, texcoord).rgb;

	gl_FragData[0].rgb = c * toonBlock * diffuse * diffuse;
	gl_FragData[1].rgb = n * 0.5 + 0.5;//takes normal and represents it as a texture
	gl_FragData[0].a = gl_FragData[1].a = 1.0;
}