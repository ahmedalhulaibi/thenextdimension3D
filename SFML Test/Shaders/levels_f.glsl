#version 120

uniform sampler2D scene;
uniform float minInput;
uniform float maxInput;
uniform float gamma;
uniform float minOutput;
uniform float maxOutput;


void main()
{
	vec3 color = texture2D(scene,gl_TexCoord[0].st).rgb;


	gl_FragColor.rgb = color;
	gl_FragColor.rgb = (pow(((color) - vec3(minInput)) / (vec3(maxInput) - vec3(minInput)),
                vec3(gamma)) * (vec3(maxOutput) - vec3(minOutput)) + vec3(minOutput));
}