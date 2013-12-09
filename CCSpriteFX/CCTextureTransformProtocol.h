//
//  CCTextureTransformProtocol.h
//  CCSpriteFX
//
//  Created by bman on 10/25/13.
//
//

#ifndef __CCTextureTransformProtocol__
#define __CCTextureTransformProtocol__

#include "cocos-ext.h"

NS_CC_EXT_BEGIN


class CC_DLL TextureTransformProtocol {
    
public:
    virtual ~TextureTransformProtocol () {};
    
    // texture crood
    virtual float getTexAnchorOffsetX () = 0;
    virtual void setTexAnchorOffsetX (float value) = 0;
    virtual float getTexAnchorOffsetY () = 0;
    virtual void setTexAnchorOffsetY (float value) = 0;
    
    // texture crood
    virtual float getTexOffsetX () = 0;
    virtual void setTexOffsetX (float value) = 0;
    virtual float getTexOffsetY () = 0;
    virtual void setTexOffsetY (float value) = 0;
    
    // clockwise
    virtual float getTexRotation () = 0;
    virtual void setTexRotation (float value) = 0;
    
    virtual float getTexScaleX () = 0;
    virtual void setTexScaleX (float value) = 0;
    virtual float getTexScaleY () = 0;
    virtual void setTexScaleY (float value) = 0;
    
    // degree
    virtual float getTexSkewX () = 0;
    virtual void setTexSkewX (float value) = 0;
    virtual float getTexSkewY () = 0;
    virtual void setTexSkewY (float value) = 0;
    
};


NS_CC_EXT_END

#endif /* defined(__CCTextureTransform__CCTextureTransformProtocol__) */
