#version 120



uniform sampler2D scene;
uniform sampler2D bloom;
uniform float gam;

vec3 screen(vec3 color1, vec3 color2)
{

	return (1.0 - ( (1.0 - color1) * (1.0- color2) ) );
}

vec3 levels(vec3 color, float minInput,
float maxInput,
float gamma,
float minOutput,
float maxOutput)
{

	//levels input range
	color = min(max(color - vec3(minInput), vec3(0.0)) / (vec3(maxInput) - vec3(minInput)), vec3(1.0));
	
	//gamma correction
	color = pow(color, vec3(1.0 / gamma));

	//levels output range
	color = mix(vec3(minOutput), vec3(maxOutput), color);

	return color;
}

void main()
{
	vec3 colorA = texture2D(scene, gl_TexCoord[0].st).rgb;
	vec3 colorB = texture2D(bloom,gl_TexCoord[0].st).rgb;
	vec3 colorC = screen(colorA,colorB);
	gl_FragColor = vec4(levels(colorC,0,1.0,gam,0,1),1);
}