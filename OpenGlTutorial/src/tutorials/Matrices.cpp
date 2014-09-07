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

#include "Matrices.h"

#include "cinder/gl/VboMesh.h"
#include "cinder/gl/GlslProg.h"

using namespace std;
using namespace cinder;

void Matrices::setup()
{
  // Our vertex positions
  vector<vec3> position = {
    vec3( -1.0f, -1.0f, 0.0f ),
    vec3( 1.0f, -1.0f, 0.0f ),
    vec3( 0.0f,  1.0f, 0.0f ),
  };

  // Upload our positions to the GPU.
  // This performs the genBuffers and buffers our data.
  gl::VboRef positionBuffer = gl::Vbo::create( GL_ARRAY_BUFFER, position );

  // BufferLayout describes what data is in our position buffer.
  // This determines the settings passed to glVertexAttribPointer.
  geom::BufferLayout layout;
  layout.append( geom::Attrib::POSITION, 3, 0, 0 );

  // Cache vertex attribute info describing our VBO in a VAO so we can draw it.
  auto mesh = gl::VboMesh::create( position.size(), GL_TRIANGLES, { { layout, positionBuffer } } );

  // Load shader programs from our assets folder.
  auto shader = gl::GlslProg::create( gl::GlslProg::Format()
                                 .vertex( app::loadAsset( "02/noTransform.vs" ) )
                                 .fragment( app::loadAsset( "02/red.fs" ) ) );

  mBatch = gl::Batch::create( mesh, shader );
}

void Matrices::draw()
{
  mBatch->draw();
}
