#version 330 core

uniform vec3 uColor = vec3( 1 );

in vec3 vColor;
in vec3 vNormal;
in vec3 vLightDirection;

out vec3 fColor;

void main()
{
	float cosTheta = clamp( dot( normalize(vNormal), normalize(vLightDirection) ), 0, 1 );

	fColor = uColor * vColor * cosTheta;
//	fColor += uColor * cosTheta;
}
