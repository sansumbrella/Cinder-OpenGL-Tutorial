#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/params/Params.h"
#include "cinder/Log.h"
#include "tutorials/FirstTriangle.h"
#include "tutorials/Matrices.h"
#include "tutorials/ColoredCube.h"
#include "tutorials/TexturedCube.h"
#include "tutorials/KeyboardAndMouse.h"
#include "tutorials/ModelLoading.h"
#include "tutorials/ShadowCasting.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class OpenGlTutorialApp : public App {
public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

  void buildTutorialList();
  void loadTutorial( int index );
private:
  using TutorialList = vector< pair<string, function<TutorialRef()>> >;

	params::InterfaceGlRef  mParams;

  TutorialList            mTutorialMakers;
  int                     mTutorialIndex = 0;
  int                     mPrevTutorialIndex = 0;
  TutorialRef             mCurrentTutorial = nullptr;
};

void OpenGlTutorialApp::setup()
{
  buildTutorialList();

  // Build parameters for moving through tutorial list.
	mParams = params::InterfaceGl::create( "OpenGL Tutorial", ivec2( 300, 100 ) );
  mParams->setOptions( "", "valueswidth=150" );

  vector<string> names;
  for( auto &tut : mTutorialMakers ) {
    names.push_back( tut.first );
  }
  mParams->addParam( "Current Tutorial", names, &mTutorialIndex );
  mParams->addButton( "Next Tutorial", [this] { loadTutorial( mTutorialIndex + 1 ); } );
  mParams->addButton( "Previous Tutorial", [this] { loadTutorial( mTutorialIndex - 1 ); } );
  mParams->addButton( "Reload Tutorial", [this] { loadTutorial( mTutorialIndex ); }, "key=r" );

  // load the last tutorial.
  loadTutorial( mTutorialMakers.size() - 1 );
}

void OpenGlTutorialApp::buildTutorialList()
{
  mTutorialMakers.push_back( make_pair( "02 First Triangle", &make_shared<FirstTriangle> ) );
  mTutorialMakers.push_back( make_pair( "03 Matrices", &make_shared<Matrices> ) );
  mTutorialMakers.push_back( make_pair( "04 Colored Cube", &make_shared<ColoredCube> ) );
  mTutorialMakers.push_back( make_pair( "05 Textured Cube", &make_shared<TexturedCube> ) );
  mTutorialMakers.push_back( make_pair( "06 Keyboard and Mouse", &make_shared<KeyboardAndMouse> ) );
  mTutorialMakers.push_back( make_pair( "08 Shadow Casting", &make_shared<ShadowCasting> ) );
  mTutorialMakers.push_back( make_pair( "07 Model Loading", &make_shared<ModelLoading> ) );
}

void OpenGlTutorialApp::loadTutorial( int index )
{
  if( index < 0 ) {
    index = mTutorialMakers.size() - 1;
  }
  mTutorialIndex = index % mTutorialMakers.size();
  mPrevTutorialIndex = mTutorialIndex;

  try {
    mCurrentTutorial = mTutorialMakers[mTutorialIndex].second();
    mCurrentTutorial->setup();
  }
  catch(const std::exception &exc) {
    CI_LOG_E( "Exception loading sample: " << exc.what() );
  }
}

void OpenGlTutorialApp::mouseDown( MouseEvent event )
{
}

void OpenGlTutorialApp::update()
{
  if( mPrevTutorialIndex != mTutorialIndex ) {
    loadTutorial( mTutorialIndex );
  }
  if ( mCurrentTutorial )
    mCurrentTutorial->update();
}

void OpenGlTutorialApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
  gl::ScopedBlend blendScope( false );

  if ( mCurrentTutorial )
    mCurrentTutorial->draw();

	mParams->draw();
}

void prepareSettings( App::Settings *settings )
{
  // Tutorial 1: open a window.
  // Cinder handles this one for us. We can set the starting resolution here.
  settings->setWindowSize( 1280, 720 );
  // We can specify whether we want a fullscreen window, too.
  settings->setFullScreen( false );
}

CINDER_APP( OpenGlTutorialApp, RendererGl, prepareSettings )
