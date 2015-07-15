#version 120

uniform sampler2D scene;
uniform vec2 pixelSize;

vec3 gaussianBlur(vec2 texCoord)
{
	vec3 colorOut = vec3(0.0);
	vec3 gaussianBlur[3] = vec3[]( 
							vec3(0.061,0.242, 0.061),
							vec3(0.242,0.383,0.242),
							vec3(0.061,0.242,0.061)
							);


	vec2 offset[9] = vec2[](vec2(-pixelSize.s,-pixelSize.t),
							vec2(0.0, -pixelSize.t),
							vec2(+pixelSize.s,-pixelSize.t),
							
							vec2(-pixelSize.s,0.0),
							vec2(0.0, 0.0),
							vec2(+pixelSize.s,0.0),

							vec2(-pixelSize.s,+pixelSize.t),
							vec2(0.0, -pixelSize.t),
							vec2(+pixelSize.s,+pixelSize.t)
							);
	float norm = 0.0;
	for(int i = 0; i < 3; ++i)
	{
		norm += gaussianBlur[i].x;
		norm += gaussianBlur[i].y;
		norm += gaussianBlur[i].z;
	}
	for(int i = 0; i < 3; ++i)
	{
		gaussianBlur[i].x /= norm;
		gaussianBlur[i].y /= norm;
		gaussianBlur[i].z /= norm;
	}
	colorOut += texture2D(scene, texCoord + offset[0]).rgb * gaussianBlur[0].x;
	colorOut += texture2D(scene, texCoord + offset[1]).rgb * gaussianBlur[0].y;
	colorOut += texture2D(scene, texCoord + offset[2]).rgb * gaussianBlur[0].z;
	colorOut += texture2D(scene, texCoord + offset[3]).rgb * gaussianBlur[1].x;
	colorOut += texture2D(scene, texCoord + offset[4]).rgb * gaussianBlur[1].y;
	colorOut += texture2D(scene, texCoord + offset[5]).rgb * gaussianBlur[1].z;
	colorOut += texture2D(scene, texCoord + offset[6]).rgb * gaussianBlur[2].x;
	colorOut += texture2D(scene, texCoord + offset[7]).rgb * gaussianBlur[2].y;
	colorOut += texture2D(scene, texCoord + offset[8]).rgb * gaussianBlur[2].z;

	return colorOut;
}


void main()
{
	gl_FragColor.rgb = gaussianBlur(gl_TexCoord[0].st);
}