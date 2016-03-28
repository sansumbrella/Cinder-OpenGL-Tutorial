#version 330 core

// Cinder passes in position and other inputs based on semantics.
// Notice that the type 'vec3' matches what we have in C++.
layout(location = 0) in vec4 ciPosition;
layout(location = 1) in vec3 ciNormal;

// Cinder passes in many uniforms based on semantics.
// This is the model view projection matrix.
uniform mat4 ciModelViewProjection;
uniform mat4 ciModelMatrix;
uniform mat3 ciNormalMatrix;
uniform mat4 ciViewMatrix;

out Vertex {
    vec3 Normal;
    vec3 WorldPosition;
} v;

void main()
{
    gl_Position = ciModelViewProjection * ciPosition;
    v.WorldPosition = vec3(ciModelMatrix * ciPosition);
    v.Normal = ciNormalMatrix * ciNormal;
}
