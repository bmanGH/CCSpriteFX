#ifndef __CCTextureTransformFunctionalTestScene_H__
#define __CCTextureTransformFunctionalTestScene_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCSpriteFX.h"
#include "CCActionTextureTransform.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCTextureTransformFunctionalTestScene : public Layer
{
    
protected:
    SpriteFX* spr1;
    SpriteFX* spr2;
    SpriteFX* spr3;
    SpriteFX* spr4;
    SpriteFX* spr5;
    SpriteFX* spr6;
    
public:
    static Scene* scene();
    CREATE_FUNC(CCTextureTransformFunctionalTestScene);
    
    virtual ~CCTextureTransformFunctionalTestScene ();
    
    virtual bool init();
    
    // update
    virtual void update (float delta) override;
    
    // draw
    virtual void draw (Renderer* renderer, const kmMat4 &transform, bool transformUpdated) override;
    
    // touch callback
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *event) override;
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *event) override;
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *event) override;
    virtual void onTouchesCancelled(const std::vector<Touch*>& touches, Event *event) override;
    
};

#endif // __CCHierarchiesSpriteFunctionalTestScene_H__
