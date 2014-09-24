#version 330 core

uniform vec3 uColor = vec3( 1 );

in vec3 vColor;
in vec3 vNormal;
in vec3 vLightDirection;
in vec3 vEye;
in vec3 vReflection;

out vec3 fColor;

void main()
{
	float cosTheta = clamp( dot( normalize(vNormal), normalize(vLightDirection) ), 0, 1 );
	float cosAlpha = clamp( dot( normalize(vEye), normalize(vReflection) ), 0, 1 );

	fColor = uColor * vec3( 0.2 ) +
			 uColor * cosTheta * vec3( 0.8 ) +
			 vec3( 1, 0, 1 ) * pow( cosAlpha, 3 );
}
