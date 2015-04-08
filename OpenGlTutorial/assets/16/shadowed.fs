#version 330 core

uniform sampler2D uLightMap;
uniform float     uBias = 0.0001;

in vec4 vShadowPosition;

layout (location = 0) out vec4 fColor;

void main()
{
  float visibility = 1.0;
  if (texture( uLightMap, vShadowPosition.xy ).z < vShadowPosition.z - uBias)
  {
    visibility = 0.25;
  }

  fColor.rgb = vec3( visibility );
  fColor.a = 1.0;
}
