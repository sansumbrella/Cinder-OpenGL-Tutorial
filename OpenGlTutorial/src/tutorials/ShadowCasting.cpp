//
//  Copyright (c) 2015 David Wicks, sansumbrella.com.
//  All rights reserved.
//

#include "ShadowCasting.h"
#include "cinder/Rand.h"

using namespace cinder;

void ShadowCasting::setup()
{
  const auto size = 1024;

  // Create a depth texture.
  auto tex_format = gl::Texture::Format()
                      .internalFormat( GL_DEPTH_COMPONENT16 )
                      .dataType( GL_FLOAT );
  _shadow_texture = gl::Texture::create( size, size, tex_format );

  // Create an FBO that renders to our depth texture.
  auto shadow_format = gl::Fbo::Format()
                        .attachment( GL_DEPTH_ATTACHMENT, _shadow_texture )
                        .disableColor();
  _shadow_fbo = gl::Fbo::create( size, size, shadow_format );
}

void ShadowCasting::draw()
{
  double t = app::getElapsedSeconds();
  gl::ScopedMatrices matrices;

  vec3 lightInvDir = vec3(0.5f, 2, 2);

  // Compute the MVP matrix from the light's point of view
  mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
  mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  mat4 depthModelMatrix = glm::mat4(1.0);
  mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

  {
    gl::ScopedFramebuffer fbo(_shadow_fbo);
    gl::ScopedViewport    viewport(ivec2(0), _shadow_fbo->getSize());
    gl::ScopedMatrices matrices;
    gl::setModelMatrix( depthModelMatrix );
    gl::setProjectionMatrix( depthProjectionMatrix );
    gl::setViewMatrix( depthViewMatrix );

    gl::clear();
    gl::enableDepthRead();
    gl::enableDepthWrite();
    drawScene( t );
  }

  gl::ScopedViewport viewport(ivec2(0), app::getWindowSize());
  gl::setMatricesWindowPersp( app::getWindowSize() );
  gl::clear();
  gl::draw( _shadow_texture );
}

void ShadowCasting::drawScene( double atTime ) const
{
  Rand r( atTime );

  for( int i = 0; i < 20; ++i ) {
    gl::drawCube( r.nextVec3f() * 5.0f, vec3( glm::mix( 1.5f, 3.0f, r.nextFloat() * r.nextFloat() ) ) );
  }
}
