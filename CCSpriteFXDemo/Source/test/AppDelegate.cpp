#include "AppDelegate.h"

#include "cocos2d.h"
#include "MainMenuScene.h"

USING_NS_CC;


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director & GLView
    Director *director = Director::getInstance();
    GLView* glView = Director::getInstance()->getOpenGLView();
    director->setProjection(Director::Projection::_2D);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
//    Scene *scene = CCColorMatrixFunctionalTestScene::scene();
    Scene *scene = MainMenuScene::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::getInstance()->pause();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::getInstance()->resume();
}
