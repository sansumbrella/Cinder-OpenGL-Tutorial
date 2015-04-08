#version 330 core

// Cinder passes in position and other inputs based on semantics.
// Notice that the type 'vec3' matches what we have in C++.
layout(location = 0) in vec3 ciPosition;

uniform mat4 ciModelViewProjection;

void main()
{
	gl_Position = ciModelViewProjection * vec4(ciPosition, 1.0);
}
