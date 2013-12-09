//
//  ColorMatrixProtocol.h
//  CCSpriteFX
//
//  Created by bman on 13-7-19.
//
//

#ifndef _ColorMatrixProtocol_h
#define _ColorMatrixProtocol_h

#include "cocos-ext.h"
#include "CCColorMatrix.h"

NS_CC_EXT_BEGIN


class CC_DLL ColorMatrixProtocol {
    
public:
    virtual ~ColorMatrixProtocol () {};
    
    virtual void setColorMatrix (const ColorMatrix4x4& colorMatrix) = 0;
    virtual ColorMatrix4x4 getColorMatrix () = 0;
    virtual void concatColorMatrix (const ColorMatrix4x4& colorMatrix) = 0;
    
    virtual void setNeedResetColorMatrixAfterDraw (bool value) = 0;
    virtual bool isNeedResetColorMatrixAfterDraw () = 0;
    
};


NS_CC_EXT_END

#endif
