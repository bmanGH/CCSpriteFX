//
//  CCPathRenderingPaint.cpp
//  CCSpriteFXDemo
//
//  Created by bman on 2/9/14.
//
//

#include "CCPathRenderingPaint.h"
#include <cassert>

NS_CC_EXT_BEGIN


PathRenderingPaint::PathRenderingPaint (PaintType type)
{
}

PathRenderingPaint::~PathRenderingPaint ()
{
}


#pragma mark - Clonable

cocos2d::Clonable* PathRenderingPaint::clone () const {
    //TODO
    return nullptr;
}


#pragma mark - internal

void PathRenderingPaint::buildGradientImage (float width, float height) {
    
}


NS_CC_EXT_END
