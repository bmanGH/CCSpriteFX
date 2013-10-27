#ifndef __CCColorMatrixFunctionalTestScene_H__
#define __CCColorMatrixFunctionalTestScene_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCSpriteFX.h"
#include "CCActionColorMatrix.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCColorMatrixFunctionalTestScene : public Layer
{
private:
    SpriteFX* spr1;
    SpriteFX* spr2;
    SpriteFX* spr3;
    SpriteFX* spr4;
    SpriteFX* spr5;
    SpriteFX* spr6;
    SpriteFX* spr7;
    SpriteFX* spr8;
    SpriteFX* spr9;
    
public:
    static Scene* scene();
    CREATE_FUNC(CCColorMatrixFunctionalTestScene);
    
    virtual ~CCColorMatrixFunctionalTestScene ();
    
    virtual bool init();
    
    // update
    virtual void update (float delta) override;
    
    // draw
    virtual void draw () override;
    
    // touch callback
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *event) override;
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *event) override;
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *event) override;
    virtual void onTouchesCancelled(const std::vector<Touch*>& touches, Event *event) override;
};

#endif // __GraphicsEffectFunctionalTestScene_H__
