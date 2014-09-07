#version 330 core

// Cinder passes in position and other inputs based on semantics.
// Notice that the type 'vec3' matches what we have in C++.
layout(location = 0) in vec3 ciPosition;

void main()
{
	gl_Position.xyz = ciPosition;
	gl_Position.w = 1.0;
}
