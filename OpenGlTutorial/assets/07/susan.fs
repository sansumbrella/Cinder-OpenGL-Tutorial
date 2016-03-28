#version 330 core

uniform vec3 uColor = vec3( 1 );
uniform vec3 uLightPosition = vec3( -1000.0, 500.0, 2000.0 );

in Vertex {
    vec3 Normal;
    vec3 WorldPosition;
} v;

out vec3 fColor;

void main()
{
    vec3 n = normalize(v.Normal);
    vec3 l = normalize(uLightPosition - v.WorldPosition);
    float diffuse = max(dot(n, l), 0.0);
    fColor = vec3(diffuse);
}
