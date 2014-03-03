//
//  CCPathRenderingShader.h
//  CCPathRendering
//
//  Created by bman on 3/3/14.
//
//

#ifndef __CCSpriteFXDemo__CCPathRenderingShader__
#define __CCSpriteFXDemo__CCPathRenderingShader__

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN


#define kCCShader_PathRendering_PositionColor "Shader_PathRendering_PositionColor"
extern CC_DLL const GLchar* ccShader_PathRendering_PositionColor_vert;
extern CC_DLL const GLchar* ccShader_PathRendering_PositionColor_frag;

#define kCCShader_PathRendering_PositionTexture "Shader_PathRendering_PositionTexture"
extern CC_DLL const GLchar* ccShader_PathRendering_PositionTexture_vert;
extern CC_DLL const GLchar* ccShader_PathRendering_PositionTexture_frag;


NS_CC_EXT_END


#endif /* defined(__CCPathRendering__CCPathRenderingShader__) */
