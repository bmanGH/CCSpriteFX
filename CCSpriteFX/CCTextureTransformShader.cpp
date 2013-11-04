//
//  CCTextureTransformShader.cpp
//  CCSpriteFX
//
//  Created by bman on 10/25/13.
//
//

#include "CCTextureTransformShader.h"

NS_CC_EXT_BEGIN


#define STRINGIZE(x) #x
#define SHADER_STRING(x) STRINGIZE(x)

const GLchar* ccShader_PositionTextureColorTextureTransform_vert = SHADER_STRING
(
#ifdef GL_ES
precision highp float;
#endif
 
uniform mat3 u_texMatrix;
 
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_fragmentColor = a_color;
    v_texCoord = (u_texMatrix * vec3(a_texCoord, 1.0)).xy;
}
);


NS_CC_EXT_END
