//
//  CCSpriteFX.h
//  CCSpriteFX
//
//  Created by bman on 10/25/13.
//
//

#ifndef __CCSpriteFX__
#define __CCSpriteFX__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "CCColorMatrixProtocol.h"
#include "CCTextureTransformProtocol.h"

NS_CC_EXT_BEGIN


extern bool kCCProfilerCategorySpriteFX;

class CC_DLL SpriteFX : public cocos2d::Sprite, public ColorMatrixProtocol, public TextureTransformProtocol {
    
protected:
    ColorMatrix4x4 _colorMatrix;
    GLint _colorMatrixUniformLocation;
    bool _needResetColorMatrix;
    
    float _texAnchorOffsetX;
    float _texAnchorOffsetY;
    float _texOffsetX;
    float _texOffsetY;
    float _texRotation;
    float _texScaleX;
    float _texScaleY;
    float _texSkewX;
    float _texSkewY;
    kmMat3 _texMatrix;
    bool _isTexTransformDirty;
    GLint _texMatrixUniformLocation;
    CustomCommand _customRenderCommand;
    
    SpriteFX ();
    virtual ~SpriteFX ();
    
    void updateShader ();
    void updateTexMatrix ();
    
public:
    static SpriteFX* create();
    static SpriteFX* create(const char *pszFileName);
    static SpriteFX* create(const char *pszFileName, const Rect& rect);
    static SpriteFX* createWithTexture(Texture2D *pTexture);
    static SpriteFX* createWithTexture(Texture2D *pTexture, const Rect& rect);
    static SpriteFX* createWithSpriteFrame(SpriteFrame *pSpriteFrame);
    static SpriteFX* createWithSpriteFrameName(const char *pszSpriteFrameName);
    
    void setTextureWrapRepeat ();
    void setTextureWrapMirroredRepeat ();
    void setTextureWrapClampToEdge ();
    
    // render
    virtual void setTexture(const std::string& fileName) override;
    virtual void setTexture(Texture2D *texture) override;
    virtual void draw (Renderer* renderer, const kmMat4 &transform, bool transformUpdated) override;
    void render ();
    
    // ColorMatrixProtocol
    virtual void setColorMatrix (const ColorMatrix4x4& colorMatrix) override;
    virtual ColorMatrix4x4 getColorMatrix () override;
    virtual void concatColorMatrix (const ColorMatrix4x4& colorMatrix) override;
    virtual void setNeedResetColorMatrixAfterDraw (bool value) override;
    virtual bool isNeedResetColorMatrixAfterDraw () override;
    
    // TextureTransformProtocol
    virtual float getTexAnchorOffsetX () override;
    virtual void setTexAnchorOffsetX (float value) override;
    virtual float getTexAnchorOffsetY () override;
    virtual void setTexAnchorOffsetY (float value) override;
    virtual float getTexOffsetX () override;
    virtual void setTexOffsetX (float value) override;
    virtual float getTexOffsetY () override;
    virtual void setTexOffsetY (float value) override;
    virtual float getTexRotation () override;
    virtual void setTexRotation (float value) override;
    virtual float getTexScaleX () override;
    virtual void setTexScaleX (float value) override;
    virtual float getTexScaleY () override;
    virtual void setTexScaleY (float value) override;
    virtual float getTexSkewX () override;
    virtual void setTexSkewX (float value) override;
    virtual float getTexSkewY () override;
    virtual void setTexSkewY (float value) override;
    
private:
    typedef cocos2d::Sprite super;
    CC_DISALLOW_COPY_AND_ASSIGN(SpriteFX);
    
};


NS_CC_EXT_END

#endif /* defined(__CCTextureTransform__CCSpriteFX__) */
