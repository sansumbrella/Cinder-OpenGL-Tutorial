#version 330 core

// Cinder passes in position and other inputs based on semantics.
// Notice that the type 'vec3' matches what we have in C++.
layout(location = 0) in vec3 ciPosition;
layout(location = 1) in vec3 ciNormal;

// Cinder passes in many uniforms based on semantics.
// This is the model view projection matrix.
uniform mat4 ciModelViewProjection;
uniform mat4 ciModelView;
uniform mat4 ciModelViewInverseTranspose;
uniform mat4 ciViewMatrix;
uniform vec3 uLightPosition = vec3( 50, 150, 50 );

// normal in camera space
out vec3 vNormal;
// from vertex to light in camera space
out vec3 vLightDirection;
out vec3 vColor;
out vec3 vEye;
out vec3 vReflection;

void main()
{
  gl_Position = ciModelViewProjection * vec4( ciPosition, 1.0 );
  vColor = (ciPosition + vec3( 1 )) / 2.0f;

  vec3 csPosition = (ciModelView * vec4( ciPosition, 1 )).xyz;
  vec3 csEyeDirection = vec3( 0 ) - csPosition;

  vec3 csLightPosition = (ciViewMatrix * vec4( uLightPosition, 1 )).xyz;

  vLightDirection = csLightPosition + csEyeDirection;

  vec3 normal = (ciModelViewInverseTranspose * vec4( ciNormal, 0 )).xyz;
  vNormal = (ciModelView * vec4( ciNormal, 0 ) ).xyz;
//  vNormal = normal;
  vEye = normalize( csEyeDirection );
  vReflection = reflect( -vLightDirection, normal );
}
