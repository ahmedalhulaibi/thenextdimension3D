#version 120

uniform sampler2D scene;
uniform sampler2D ramp;

void main()
{
	vec3 color = texture2D(scene, gl_TexCoord[0].st).rgb;
	vec3 outColor;
	outColor.r = texture2D(ramp, vec2(color.x , 0.0)).r;
	outColor.g = texture2D(ramp, vec2(color.y , 0.0)).g;
	outColor.b = texture2D(ramp, vec2(color.z , 0.0)).b;
	gl_FragColor.rgb = outColor;
}