//
//  CCColorMatrixShader.h
//  CCSpriteFX
//
//  Created by bman on 13-7-19.
//
//

#ifndef __ColorMatrixShader__
#define __ColorMatrixShader__

#include "cocos2d.h"

namespace cocos2d { namespace extension {


#define kCCShader_PositionTextureColorColorMatrixPremultipliedAlpha "ShaderPositionTextureColorColorMatrixPremultipliedAlpha"
extern CC_DLL const GLchar* ccShader_PositionTextureColorColorMatrixPremultipliedAlpha_frag;

#define kCCShader_PositionTextureColorColorMatrix  "ShaderPositionTextureColorColorMatrix"
extern CC_DLL const GLchar* ccShader_PositionTextureColorColorMatrix_frag;


}}

#endif /* defined(__ColorMatrixShader__) */
