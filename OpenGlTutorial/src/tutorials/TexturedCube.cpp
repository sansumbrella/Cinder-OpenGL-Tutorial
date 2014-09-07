/*
 * Copyright (c) 2014 David Wicks, sansumbrella.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "TexturedCube.h"

#include "cinder/gl/Texture.h"
#include "cinder/gl/GlslProg.h"

using namespace std;
using namespace cinder;

void TexturedCube::setup()
{

  mTexture = gl::Texture::create( loadImage( app::loadAsset( "05/texture-01.jpg" ) ) );

  auto shader = gl::GlslProg::create( gl::GlslProg::Format()
                                     .vertex( app::loadAsset( "05/texture.vs" ) )
                                     .fragment( app::loadAsset( "05/texture.fs" ) )
                                     );

  mBatch = gl::Batch::create( geom::Cube().enable( geom::TEX_COORD_0 ), shader );

}

void TexturedCube::draw()
{
  gl::enableDepthWrite();
  gl::enableDepthRead();

  gl::ScopedTextureBind tex0( mTexture );

  float t = app::getElapsedSeconds() * 2.0f;
  mat4 projection = glm::perspective( 45.0f, app::getWindowWidth() / (float) app::getWindowHeight(), 0.1f, 100.0f );
  mat4 view = glm::lookAt( vec3( 4, 3, 3 ), vec3( 0, 0, 0 ), vec3( 0, 1, 0 ) );
  mat4 model = glm::eulerAngleXY( t * 0.13f, t * 0.37f );
  mat4 mvp = projection * view * model;

  mBatch->getGlslProg()->uniform( "uColorMap", 0 );
  mBatch->getGlslProg()->uniform( "uMVP", mvp );
  mBatch->getGlslProg()->uniform( "uColor", vec3( 1 ) );
  mBatch->draw();
}
