#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/params/Params.h"

#include "FirstTriangle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class OpenGlTutorialApp : public AppNative {
public:
	void prepareSettings( Settings *settings ) override;
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

void OpenGlTutorialApp::prepareSettings( Settings *settings )
{
	// Tutorial 1: open a window.
	// Cinder handles this one for us. We can set the starting resolution here.
	settings->setWindowSize( 1280, 720 );
	// We can specify whether we want a fullscreen window, too.
	settings->setFullScreen( false );
}

void OpenGlTutorialApp::setup()
{
  buildTutorialList();

	mParams = params::InterfaceGl::create( "OpenGL Tutorial", ivec2( 300, 100 ) );

  vector<string> names;
  for( auto &tut : mTutorialMakers ) {
    names.push_back( tut.first );
  }
  mParams->addParam( "Current Tutorial", names, &mTutorialIndex );
  mParams->addButton( "Next Tutorial", [this] { loadTutorial( mTutorialIndex + 1 ); } );
  mParams->addButton( "Previous Tutorial", [this] { loadTutorial( mTutorialIndex - 1 ); } );

  loadTutorial( 0 );
}

void OpenGlTutorialApp::buildTutorialList()
{
  mTutorialMakers.push_back( make_pair( "First Triangle", &make_shared<FirstTriangle> ) );
  mTutorialMakers.push_back( make_pair( "Just Like the First Triangle", &make_shared<FirstTriangle> ) );
}

void OpenGlTutorialApp::loadTutorial( int index )
{
  if( index < 0 ) {
    index = mTutorialMakers.size() - 1;
  }
  mTutorialIndex = index % mTutorialMakers.size();
  mPrevTutorialIndex = mTutorialIndex;

  mCurrentTutorial = mTutorialMakers[mTutorialIndex].second();
  mCurrentTutorial->setup();
}

void OpenGlTutorialApp::mouseDown( MouseEvent event )
{
}

void OpenGlTutorialApp::update()
{
  if( mPrevTutorialIndex != mTutorialIndex ) {
    loadTutorial( mTutorialIndex );
  }
  mCurrentTutorial->update();
}

void OpenGlTutorialApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );

  mCurrentTutorial->draw();

	mParams->draw();
}

CINDER_APP_NATIVE( OpenGlTutorialApp, RendererGl )
