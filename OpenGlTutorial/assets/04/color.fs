#version 330 core

uniform vec3 uColor;

in vec3 vColor;

out vec3 fColor;

void main()
{
	fColor = uColor * vColor;
}
