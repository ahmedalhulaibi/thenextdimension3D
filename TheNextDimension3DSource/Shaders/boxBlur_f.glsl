#version 120



uniform sampler2D scene;
uniform vec2 pixelSize; //uv difference between one pixel, 
						//x & y displacement from pixel to pixel


vec3 BoxBlur(vec2 texCoord)
{
	vec3 colorOut = vec3(0.0);

	vec2 offset[9] = vec2[]( vec2(-pixelSize.s,-pixelSize.t),
							vec2(0.0, -pixelSize.t),
							vec2(+pixelSize.s,-pixelSize.t),

							vec2(-pixelSize.s,0.0),
							vec2(0.0, 0.0),
							vec2(+pixelSize.s,0.0),

							vec2(-pixelSize.s,+pixelSize.t),
							vec2(0.0, -pixelSize.t),
							vec2(+pixelSize.s,+pixelSize.t)
							);

	for( int i = 0; i < 9; ++i)
	{
		colorOut += texture2D(scene, texCoord + offset[i]).rgb;
	}

	return (colorOut/9.0);
}

void main()
{
	gl_FragColor.rgb = BoxBlur(gl_TexCoord[0].st);
}