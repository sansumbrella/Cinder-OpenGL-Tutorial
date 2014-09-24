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

#include "KeyboardAndMouse.h"

#include "cinder/app/App.h"
#include "cinder/gl/VboMesh.h"
#include "cinder/gl/GlslProg.h"


using namespace std;
using namespace cinder;
using app::KeyEvent;
using app::MouseEvent;

void KeyboardAndMouse::setup()
{
  auto shader = gl::GlslProg::create( gl::GlslProg::Format()
                                     .vertex( app::loadAsset( "06/mvp.vs" ) )
                                     .fragment( app::loadAsset( "06/color.fs" ) ) );

  mCubeBatch = gl::Batch::create( geom::Cube(), shader );

  // Get a reference to the currently active window
  app::WindowRef window = app::getWindow();

  // Store the connection from the window's mouse move event to this.
  // Storing the connection ensures it's closed when this object is destructed.
  connectionManager().store( window->getSignalMouseMove().connect( [this] ( const app::MouseEvent &event )
                                                                  {
                                                                    mMousePos = event.getPos();
                                                                    mPrevMousePos = mMousePos;
                                                                  } )
  );

  connectionManager().store( window->getSignalMouseDrag().connect( [this] ( const app::MouseEvent &event )
                                                                  {
                                                                    mMousePos = event.getPos();
                                                                  } )
                            );
  connectionManager().store( window->getSignalKeyDown().connect( [this] ( const KeyEvent &event )
                                                               {
                                                                 switch ( event.getCode() ) {
                                                                   case KeyEvent::KEY_UP :
                                                                     mKeyVelocity.y = 1;
                                                                     break;
                                                                   case KeyEvent::KEY_DOWN :
                                                                     mKeyVelocity.y = -1;
                                                                     break;
                                                                   case KeyEvent::KEY_LEFT :
                                                                     mKeyVelocity.x = -1;
                                                                     break;
                                                                   case KeyEvent::KEY_RIGHT :
                                                                     mKeyVelocity.x = 1;
                                                                     break;
                                                                   default:
                                                                     break;
                                                                 }
                                                               } )
                            );
  connectionManager().store( window->getSignalKeyUp().connect( [this] ( const KeyEvent &event )
                                                                {
                                                                  switch ( event.getCode() ) {
                                                                    case KeyEvent::KEY_UP :
                                                                      mKeyVelocity.y = 0;
                                                                      break;
                                                                    case KeyEvent::KEY_DOWN :
                                                                      mKeyVelocity.y = 0;
                                                                      break;
                                                                    case KeyEvent::KEY_LEFT :
                                                                      mKeyVelocity.x = 0;
                                                                      break;
                                                                    case KeyEvent::KEY_RIGHT :
                                                                      mKeyVelocity.x = 0;
                                                                      break;
                                                                    default:
                                                                      break;
                                                                  }
                                                                } )
                            );

  connectionManager().store( window->getSignalMouseWheel().connect( [this] ( const MouseEvent &event )
  {
    mFov += event.getWheelIncrement();
  } ) );

  mFrameTimer.start();
}

void KeyboardAndMouse::update()
{
  float dt = mFrameTimer.getSeconds();
  mFrameTimer.start();

  mViewAngles += mMouseSpeed * dt * (mMousePos - mPrevMousePos);
  mPrevMousePos = mMousePos;

  vec3 direction( cos( mViewAngles.y ) * sin( mViewAngles.x ),
                 sin( mViewAngles.y ),
                 cos( mViewAngles.y ) * cos( mViewAngles.x ) );

  vec3 right( sin( mViewAngles.x - M_PI / 2.0f ), 0, cos( mViewAngles.x - M_PI / 2.0f ) );
  vec3 up = cross( right, direction );

  mPosition += direction * mKeyVelocity.y * dt * mSpeed + right * mKeyVelocity.x * dt * mSpeed;

  mProjectionMatrix = glm::perspective( mFov, app::getWindowAspectRatio(), 0.1f, 100.0f );
  mViewMatrix = glm::lookAt( mPosition, mPosition + direction, up );
}

void KeyboardAndMouse::draw()
{
  // Turn on backface culling for the scope of this function.
  gl::ScopedFaceCulling cull( true, GL_BACK );

  mCubeBatch->getGlslProg()->uniform( "uMVP", mProjectionMatrix * mViewMatrix );
  mCubeBatch->getGlslProg()->uniform( "uColor", vec3( 1 ) );
  mCubeBatch->draw();
}
