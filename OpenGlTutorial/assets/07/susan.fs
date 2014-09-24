#version 330 core

uniform vec3 uColor = vec3( 1 );

in vec3 vColor;

out vec3 fColor;

void main()
{
	fColor = uColor * vColor;
}
