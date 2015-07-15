#version 120

uniform sampler2D scene;

void main()
{
	vec3 color = texture2D(scene,gl_TexCoord[0].st).rgb;
	float grayscale = dot(color,vec3(0.222,0.707,0.071));
	gl_FragColor = vec4(grayscale,grayscale,grayscale,1.0);
}