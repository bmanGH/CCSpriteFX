//
//  MainMenuScene.h
//  CCTextureTransform
//
//  Created by bman on 10/27/13.
//
//

#ifndef __CCTextureTransform__MainMenuScene__
#define __CCTextureTransform__MainMenuScene__

#include "cocos2d.h"

USING_NS_CC;


class MainMenuScene : public Layer
{
    
public:
    static Scene* scene();
    CREATE_FUNC(MainMenuScene);
    
    virtual ~MainMenuScene ();
    
    virtual bool init();
    
};

#endif /* defined(__CCTextureTransform__MainMenuScene__) */
