/*
 * Copyright (c) 2014 David Wicks,  sansumbrella.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms,  with or
 * without modification,  are permitted provided that the following
 * conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice,  this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice,  this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
 * LIMITED TO,  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,  INDIRECT,  INCIDENTAL,
 * SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL DAMAGES (INCLUDING,  BUT NOT
 * LIMITED TO,  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA,  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY,  WHETHER IN CONTRACT,  STRICT LIABILITY,  OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE,  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ColoredCube.h"

#include "cinder/gl/VboMesh.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/GeomIo.h"

using namespace std;
using namespace cinder;

void ColoredCube::setup()
{
  vector<vec3> cubePositions = {
    vec3( -1.0f, -1.0f, -1.0f ),  // triangle 1 : begin
    vec3( -1.0f, -1.0f,  1.0f ),
    vec3( -1.0f,  1.0f,  1.0f ),  // triangle 1 : end
    vec3( 1.0f,  1.0f, -1.0f ),  // triangle 2 : begin
    vec3( -1.0f, -1.0f, -1.0f ),
    vec3( -1.0f,  1.0f, -1.0f ),  // triangle 2 : end
    vec3( 1.0f, -1.0f,  1.0f ),
    vec3( -1.0f, -1.0f, -1.0f ),
    vec3( 1.0f, -1.0f, -1.0f ),
    vec3( 1.0f,  1.0f, -1.0f ),
    vec3( 1.0f, -1.0f, -1.0f ),
    vec3( -1.0f, -1.0f, -1.0f ),
    vec3( -1.0f, -1.0f, -1.0f ),
    vec3( -1.0f,  1.0f,  1.0f ),
    vec3( -1.0f,  1.0f, -1.0f ),
    vec3( 1.0f, -1.0f,  1.0f ),
    vec3( -1.0f, -1.0f,  1.0f ),
    vec3( -1.0f, -1.0f, -1.0f ),
    vec3( -1.0f,  1.0f,  1.0f ),
    vec3( -1.0f, -1.0f,  1.0f ),
    vec3( 1.0f, -1.0f,  1.0f ),
    vec3( 1.0f,  1.0f,  1.0f ),
    vec3( 1.0f, -1.0f, -1.0f ),
    vec3( 1.0f,  1.0f, -1.0f ),
    vec3( 1.0f, -1.0f, -1.0f ),
    vec3( 1.0f,  1.0f,  1.0f ),
    vec3( 1.0f, -1.0f,  1.0f ),
    vec3( 1.0f,  1.0f,  1.0f ),
    vec3( 1.0f,  1.0f, -1.0f ),
    vec3( -1.0f,  1.0f, -1.0f ),
    vec3( 1.0f,  1.0f,  1.0f ),
    vec3( -1.0f,  1.0f, -1.0f ),
    vec3( -1.0f,  1.0f,  1.0f ),
    vec3( 1.0f,  1.0f,  1.0f ),
    vec3( -1.0f,  1.0f,  1.0f ),
    vec3( 1.0f, -1.0f,  1.0f )
  };

  auto buffer = gl::Vbo::create( GL_ARRAY_BUFFER, cubePositions );
  geom::BufferLayout layout;
  layout.append( geom::Attrib::POSITION, 3, 0, 0 );
  auto mesh = gl::VboMesh::create( cubePositions.size(), GL_TRIANGLES, { { layout, buffer } } );
  auto shader = gl::GlslProg::create( gl::GlslProg::Format()
                                     .vertex( app::loadAsset( "04/mvp.vs" ) )
                                     .fragment( app::loadAsset( "04/color.fs" ) ) );

  mCubeBatch = gl::Batch::create( mesh, shader );

//  mAltCubeBatch = gl::Batch::create( geom::Cube(), shader );
}

void ColoredCube::draw()
{
  mat4 model( 1 );
  mat4 view = glm::lookAt( vec3( 4, 3, 3 ), vec3( 0, 0, 0 ), vec3( 0, 1, 0 ) );
  mat4 projection = glm::perspective( 45.0f, app::getWindowWidth() / (float)app::getWindowHeight(), 0.1f, 100.0f );

  mat4 mvp = projection * view * model;
  mCubeBatch->getGlslProg()->uniform( "uMVP", mvp );
  mCubeBatch->getGlslProg()->uniform( "uColor", vec3( 1 ) );
  mCubeBatch->draw();
//  mAltCubeBatch->draw();
}
