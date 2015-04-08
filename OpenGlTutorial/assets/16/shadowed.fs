#version 330 core

uniform sampler2DShadow uLightMap;
uniform float           uBias = 0.01;

in vec4 vShadowPosition;

layout (location = 0) out vec4 fColor;

const vec2 poissonDisk[4] = vec2[](
                             vec2( -0.94201624, -0.39906216 ),
                             vec2( 0.94558609, -0.76890725 ),
                             vec2( -0.094184101, -0.92938870 ),
                             vec2( 0.34495938, 0.29387760 )
                             );

void main()
{
  float visibility = 1.0;

  for (int i = 0; i < 4; i += 1 )
  {
    visibility -= 0.2 * texture(uLightMap, vec3(vShadowPosition.xy + poissonDisk[i]/700.0, (vShadowPosition.z - uBias) / vShadowPosition.w ));
  }

  fColor.rgb = vec3( visibility );
  fColor.a = 1.0;
}
