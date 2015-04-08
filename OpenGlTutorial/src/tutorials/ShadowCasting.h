//
//  Copyright (c) 2015 David Wicks, sansumbrella.com.
//  All rights reserved.
//

#pragma once

#include "TutorialBase.h"

class ShadowCasting : public TutorialBase
{
public:
  void setup() override;
  void draw() override;

  void drawScene( double atTime ) const;
private:

  ci::gl::FboRef      _shadow_fbo;
  ci::gl::TextureRef  _shadow_texture;

  ci::gl::GlslProgRef _shadowed_prog;
  ci::CameraPersp     _camera;
};
