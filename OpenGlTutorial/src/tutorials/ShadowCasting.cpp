//
//  Copyright (c) 2015 David Wicks, sansumbrella.com.
//  All rights reserved.
//

#include "ShadowCasting.h"
#include "cinder/Rand.h"

using namespace cinder;

void ShadowCasting::setup()
{
  const auto size = 2048;

  // Create a depth texture.
  auto tex_format = gl::Texture::Format()
                      .internalFormat( GL_DEPTH_COMPONENT16 )
                      .swizzleMask( GL_RED, GL_RED, GL_RED, GL_RED )
                      .compareMode( GL_COMPARE_REF_TO_TEXTURE )
                      .compareFunc( GL_GREATER )
                      .dataType( GL_FLOAT );
  _shadow_texture = gl::Texture::create( size, size, tex_format );

  // Create an FBO that renders to our depth texture.
  auto shadow_format = gl::Fbo::Format()
                        .attachment( GL_DEPTH_ATTACHMENT, _shadow_texture )
                        .disableColor();
  _shadow_fbo = gl::Fbo::create( size, size, shadow_format );

  _shadowed_prog = gl::GlslProg::create(gl::GlslProg::Format()
                                          .fragment(app::loadAsset("16/shadowed.fs"))
                                          .vertex(app::loadAsset("16/shadowed.vs")));

  _camera = CameraPersp( app::getWindowAspectRatio() * 20.0f, 20.0f, 35.0f, 0.1f, 50.0f );
  _camera.lookAt( vec3( 0.0f, 0.5f, 20.0f ), vec3( 0 ), vec3( 0, 1, 0 ) );
}

void ShadowCasting::draw()
{
  double t = app::getElapsedSeconds();
  gl::ScopedMatrices matrices;
  gl::ScopedFrontFace front(GL_CCW);

  vec3 lightInvDir = vec3(0.5f, 2, 2);

  // Compute the MVP matrix from the light's point of view
  mat4 depth_projection = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
  mat4 depth_view = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  mat4 model_matrix = glm::rotate<float>( t, vec3( 1.0, 0.0, 0.5 ) );
  mat4 depth_mvp = depth_projection * depth_view * model_matrix;

  // Draw scene from light's perspective
  {
    gl::ScopedFaceCulling cull(GL_FRONT, true);
    gl::ScopedFramebuffer fbo(_shadow_fbo);
    gl::ScopedViewport    viewport(ivec2(0), _shadow_fbo->getSize());
    gl::ScopedMatrices matrices;
    gl::setModelMatrix( model_matrix );
    gl::setProjectionMatrix( depth_projection );
    gl::setViewMatrix( depth_view );

    gl::clear();
    gl::enableDepthRead();
    gl::enableDepthWrite();
    drawScene( t );
  }

  // Draw scene from camera's perspective
  {
    gl::ScopedFaceCulling cull(GL_BACK, true);
    gl::ScopedViewport viewport(ivec2(0), app::getWindowSize());
    gl::ScopedGlslProg prog(_shadowed_prog);
    gl::ScopedTextureBind tex(_shadow_texture, 0);
    gl::clear();

    // Transform depth coordinates from [-1.0, 1.0] to [0, 1.0]
    mat4 bias_matrix = mat4(
                            0.5, 0.0, 0.0, 0.0,
                            0.0, 0.5, 0.0, 0.0,
                            0.0, 0.0, 0.5, 0.0,
                            0.5, 0.5, 0.5, 1.0
                            );
    mat4 depth_bias_mvp = bias_matrix * depth_mvp;
    _shadowed_prog->uniform("uDepthBiasModelViewProjection", depth_bias_mvp);
    _shadowed_prog->uniform("uLightMap", 0);

    gl::setMatrices( _camera );
    gl::setModelMatrix( model_matrix );
    drawScene( t );
  }
}

void ShadowCasting::drawScene( double atTime ) const
{
  Rand r( atTime * 0.1f );
  for( int i = 0; i < 20; ++i ) {
    gl::drawCube( r.nextVec3f() * 5.0f, vec3( glm::mix( 1.5f, 3.0f, r.nextFloat() * r.nextFloat() ) ) );
  }
}
