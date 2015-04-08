#version 330 core

layout (location = 0) out float fDepth;

void main()
{
  // This is automatically written for us, but for clarity:
  fDepth = gl_FragCoord.z;
}
