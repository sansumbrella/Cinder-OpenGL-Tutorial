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

#include "ModelLoading.h"
#include "cinder/ObjLoader.h"
#include "cinder/gl/GlslProg.h"

using namespace std;
using namespace cinder;

void ModelLoading::setup()
{
  ObjLoader loader( app::loadAsset( "07/susan.obj" ) );

  app::console() << "Monkey loaded with " << loader.getNumVertices() << " vertices." << endl;;
  mMonkeyBatch = gl::Batch::create( loader, gl::GlslProg::create( app::loadAsset( "07/susan.vs" ), app::loadAsset( "07/susan.fs" ) ) );
}

void ModelLoading::draw()
{
  gl::setMatricesWindowPersp( app::getWindowSize() );
  gl::color( Color::white() );
  gl::translate( app::getWindowCenter() );
  quat q = glm::quat_cast( glm::eulerAngleYXZ<float>( app::getElapsedSeconds() * 0.3f, app::getElapsedSeconds() * 0.5f, app::getElapsedSeconds() * 0.7f ) );
  gl::rotate( q );
  gl::scale( vec3( 180.0f ) );

  // Our model isn't properly formed for face culling to work.
//  gl::ScopedFaceCulling cull( true, GL_FRONT );
  gl::enableDepthRead();
  gl::enableDepthWrite();
  mMonkeyBatch->getGlslProg()->uniform( "uColor", Color::white() );
  mMonkeyBatch->draw();
}

