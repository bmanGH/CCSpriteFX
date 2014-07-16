//
//  ColorMatrixProtocol.h
//  CCSpriteFX
//
//  Created by bman on 13-7-19.
//
//

#ifndef _ColorMatrixProtocol_h
#define _ColorMatrixProtocol_h

#include "CCColorMatrix.h"

namespace cocos2d { namespace extension {


class CC_DLL ColorMatrixProtocol {
    
public:
    virtual ~ColorMatrixProtocol () {};
    
    virtual void setColorMatrix (const ColorMatrix4x4& colorMatrix) = 0;
    virtual ColorMatrix4x4 getColorMatrix () = 0;
    virtual void concatColorMatrix (const ColorMatrix4x4& colorMatrix) = 0;
    
    virtual void setNeedResetColorMatrixAfterDraw (bool value) = 0;
    virtual bool isNeedResetColorMatrixAfterDraw () = 0;
    
};


}}

#endif
