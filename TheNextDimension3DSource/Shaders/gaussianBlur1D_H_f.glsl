#version 120

uniform sampler2D scene;
uniform float pixelSize;

void main()
{
	vec3 gaussianBlur[3] = vec3[]( 
							vec3(0.0001,0.0003, 0.133),
							vec3(0.242,0.383,0.242),
							vec3(0.133,0.0003, 0.0001)
							);

	float norm = float(0.0);
	
	norm += gaussianBlur[1].x + gaussianBlur[1].y + gaussianBlur[1].z;
	
	vec3 color = vec3(0.0);

	color += texture2D(scene, vec2(gl_TexCoord[0].s - pixelSize,gl_TexCoord[0].t			  )).rgb * (gaussianBlur[1].x/norm);
	color += texture2D(scene, vec2(gl_TexCoord[0].s                ,gl_TexCoord[0].t			  )).rgb * (gaussianBlur[1].y/norm);
	color += texture2D(scene, vec2(gl_TexCoord[0].s + pixelSize,gl_TexCoord[0].t			  )).rgb * (gaussianBlur[1].z/norm);


	gl_FragColor  = vec4(color,1);

}