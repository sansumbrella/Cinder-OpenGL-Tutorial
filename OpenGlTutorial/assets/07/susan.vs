#version 330 core

// Cinder passes in position and other inputs based on semantics.
// Notice that the type 'vec3' matches what we have in C++.
layout(location = 0) in vec3 ciPosition;
layout(location = 1) in vec3 ciNormal;

// Cinder passes in many uniforms based on semantics.
// This is the model view projection matrix.
uniform mat4 ciModelViewProjection;

out vec3 vColor;

void main()
{
  gl_Position = ciModelViewProjection * vec4( ciPosition, 1.0 );
  vColor = (ciPosition + vec3( 1 )) / 2.0f;
//  vColor.rgb *= (ciNormal.xyz + vec3( 1 )) / 2.0f;
}
