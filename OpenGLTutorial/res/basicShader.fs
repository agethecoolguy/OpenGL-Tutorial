#version 120

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(unit, vec2(0.2, 0.2)); //vec4(1.0,0.0,0.0,1.0);
}