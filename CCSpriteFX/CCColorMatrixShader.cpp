//
//  CCColorMatrixShader.cpp
//  CCColorMatrix
//
//  Created by bman on 13-7-19.
//
//

#include "CCColorMatrixShader.h"

NS_CC_EXT_BEGIN


#define STRINGIZE(x) #x
#define SHADER_STRING(x) STRINGIZE(x)

const GLchar* ccShader_PositionTextureColorColorMatrixPremultipliedAlpha_frag = SHADER_STRING
(
#ifdef GL_ES
precision lowp float;
#endif

uniform mediump mat4 u_colorMatrix;
uniform sampler2D CC_Texture0;
 
varying vec4 v_fragmentColor;
varying highp vec2 v_texCoord;

void main()
{
    vec4 origColor = texture2D(CC_Texture0, v_texCoord);
    origColor.rgb = origColor.rgb / origColor.a;

    vec4 color = origColor;
    color.a = 1.0;
    color = u_colorMatrix * color;

    gl_FragColor = vec4(color.rgb, origColor.a);
    gl_FragColor.rgb = gl_FragColor.rgb * gl_FragColor.a;
    gl_FragColor = gl_FragColor * v_fragmentColor;
}
);

const GLchar* ccShader_PositionTextureColorColorMatrix_frag = SHADER_STRING
(
#ifdef GL_ES
precision lowp float;
#endif

uniform mediump mat4 u_colorMatrix;
uniform sampler2D CC_Texture0;

varying vec4 v_fragmentColor;
varying highp vec2 v_texCoord;

void main()
{
    vec4 origColor = texture2D(CC_Texture0, v_texCoord);

    vec4 color = origColor;
    color.a = 1.0;
    color = u_colorMatrix * color;

    gl_FragColor = vec4(color.rgb, origColor.a);
    gl_FragColor = gl_FragColor * v_fragmentColor;
}
);

NS_CC_EXT_END
