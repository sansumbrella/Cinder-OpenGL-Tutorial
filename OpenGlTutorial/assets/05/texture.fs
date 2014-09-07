#version 330 core

uniform vec3      uColor;
uniform sampler2D uColorMap;

//in vec3 vColor;
in vec2 vTexCoord;

out vec3 fColor;

void main()
{
  vec3 color = texture( uColorMap, vTexCoord ).rgb;
	fColor = uColor * color;
}
