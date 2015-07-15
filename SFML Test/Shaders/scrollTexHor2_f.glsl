#version 120

uniform sampler2D tex;
uniform float time;
uniform float speed;

void main()
{
	gl_FragColor = (texture2D(tex,vec2(gl_TexCoord[0].s + (time/-speed),gl_TexCoord[0].t)) + texture2D(tex,vec2(gl_TexCoord[0].s,gl_TexCoord[0].t)))/2;	
}