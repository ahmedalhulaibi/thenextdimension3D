/*
	Edge fragment shader

	Detect edges and blend with the input image.
*/


#version 120

// 4 uniforms
uniform sampler2D inputColour;
uniform sampler2D inputNormal;
uniform sampler2D inputDepth;
uniform vec2 pixelSize;


/* SOBEL EDGE DETECTION
	-1  0  1 Horizontal pass
	-2  0  2
	-1  0  1

	-1 -2 -1 Vertical pass
	 0  0  0
	 1  2  1
*/
//sobel edge function, return 0 if edge return 1 if not

float sobel_Horiz(sampler2D image, vec2 texCoord)
{
	vec2 offset[6] = vec2[]( vec2(-pixelSize.s,-pixelSize.t),vec2(pixelSize.s, -pixelSize.t),
							vec2(-pixelSize.s,0.0),vec2(pixelSize.s,0.0),
							vec2(-pixelSize.s, pixelSize.t),vec2(pixelSize.s,pixelSize.t)
							);

	vec3 sum = vec3(0.0);
	sum += -1.0*texture2D(image,offset[0]+texCoord).rgb;
	sum +=		texture2D(image,offset[1]+texCoord).rgb;
	sum += -2.0*texture2D(image,offset[2]+texCoord).rgb;
	sum +=  2.0*texture2D(image,offset[3]+texCoord).rgb;
	sum += -1.0*texture2D(image,offset[4]+texCoord).rgb;
	sum +=		texture2D(image,offset[5]+texCoord).rgb;
	
	float lenSq = dot(sum,sum);
	return (lenSq < 1.0 ? 1.0 : 0.0);
}

float sobel_Vert(sampler2D image, vec2 texCoord)
{
	vec2 offset[6] = vec2[]( 
							vec2(-pixelSize.s,-pixelSize.t),vec2(0.0, -pixelSize.t),vec2(pixelSize.s,-pixelSize.t),
							vec2(-pixelSize.s,pixelSize.t),vec2(0.0, pixelSize.t),vec2(pixelSize.s,pixelSize.t)
							);

	vec3 sum = vec3(0.0);
	sum += -1.0*texture2D(image,offset[0]+texCoord).rgb;
	sum += -2.0*texture2D(image,offset[1]+texCoord).rgb;
	sum += -1.0*texture2D(image,offset[2]+texCoord).rgb;
	sum +=      texture2D(image,offset[3]+texCoord).rgb;
	sum +=  2.0*texture2D(image,offset[4]+texCoord).rgb;
	sum +=		texture2D(image,offset[5]+texCoord).rgb;
	
	float lenSq = dot(sum,sum);
	return (lenSq < 1.0 ? 1.0 : 0.0);
}


void main()
{	
	vec2 texcoord = gl_TexCoord[0].st;
	
	vec3 c = texture2D(inputColour, texcoord).rgb;

	float normalSobelH = sobel_Horiz(inputNormal,texcoord);
	float normalSobelV = sobel_Vert(inputNormal,texcoord);

	float depthSobelH = sobel_Horiz(inputDepth,texcoord);
	float depthSobelV = sobel_Vert(inputDepth,texcoord);

	float colourSobelH = sobel_Horiz(inputColour,texcoord);
	float colourSobelV = sobel_Vert(inputColour,texcoord);

	float finalEdge = normalSobelH*normalSobelV
					 *depthSobelH*depthSobelV
					 /**colourSobelH*colourSobelV*/;

	gl_FragColor = vec4(/*finalEdge * */c,1);
}