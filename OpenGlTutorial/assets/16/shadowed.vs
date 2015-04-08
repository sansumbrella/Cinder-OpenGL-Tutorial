#version 330 core

// Cinder passes in position and other inputs based on semantics.
// Notice that the type 'vec3' matches what we have in C++.
layout(location = 0) in vec3 ciPosition;

uniform mat4 ciModelViewProjection;
uniform mat4 uDepthBiasModelViewProjection;

out vec4 vShadowPosition;

void main()
{
  vShadowPosition = uDepthBiasModelViewProjection * vec4(ciPosition, 1.0);
	gl_Position = ciModelViewProjection * vec4(ciPosition, 1.0);
}
