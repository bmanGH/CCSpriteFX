#ifndef __CCColorMatrixFunctionalTestScene_H__
#define __CCColorMatrixFunctionalTestScene_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCSpriteFX.h"
#include "CCActionColorMatrix.h"


#include "MonkVG/openvg.h"
#include "MonkVG/vgu.h"
#include "MonkVG/vgext.h"

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
    
    CustomCommand _customRenderCommand;
    
    VGPath	_path;
	VGPaint _paint;
	VGPaint _linearGradientPaint;
	VGPaint _radialGradientPaint;
//	VGImage _image;
//	VGImage	_bitmapFont;
	//	VGImage _gradientImage;
	VGPath _linearGradientPath;
	VGPath _radialGradientPath;
	VGFont	_font;
	VGfloat _lineHeight;
    
public:
    static Scene* scene();
    CREATE_FUNC(CCColorMatrixFunctionalTestScene);
    
    virtual ~CCColorMatrixFunctionalTestScene ();
    
    virtual bool init();
    
    // update
    virtual void update (float delta) override;
    
    // draw
    virtual void draw () override;
    void render ();
    
    // touch callback
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *event) override;
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *event) override;
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *event) override;
    virtual void onTouchesCancelled(const std::vector<Touch*>& touches, Event *event) override;
};

#endif // __GraphicsEffectFunctionalTestScene_H__
