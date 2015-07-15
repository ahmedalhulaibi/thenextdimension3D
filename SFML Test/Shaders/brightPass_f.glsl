#version 120

uniform sampler2D image;


void main()
{
	float luminance = 0.555;
	float middleGrey = 0.7;
	float threshold = 0.5;
	
	vec4 color = texture2D(image,gl_TexCoord[0].st);
	color *= (middleGrey / luminance);
	color *= (1.0+   (color / (threshold * threshold))   );
	color -= 0.5;
	color /= (1.0 + color);
	gl_FragColor= color;
}