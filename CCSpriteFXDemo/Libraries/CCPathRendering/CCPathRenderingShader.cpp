//
//  CCPathRenderingShader.cpp
//  CCPathRendering
//
//  Created by bman on 3/3/14.
//
//

#include "CCPathRenderingShader.h"

NS_CC_EXT_BEGIN


#define STRINGIZE(x) #x
#define SHADER_STRING(x) STRINGIZE(x)

const GLchar* ccShader_PathRendering_PositionColor_vert = SHADER_STRING
(
#ifdef GL_ES
precision highp float;
#endif

attribute vec4 a_position;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
}
);

const GLchar* ccShader_PathRendering_PositionColor_frag = SHADER_STRING
(
#ifdef GL_ES
precision lowp float;
#endif
 
uniform vec4 u_color;
 
void main()
{
    gl_FragColor = u_color;
}
);

const GLchar* ccShader_PathRendering_PositionTexture_vert = SHADER_STRING
(
#ifdef GL_ES
precision highp float;
#endif
 
attribute vec4 a_position;
attribute vec2 a_texCoord;
 
varying vec2 v_texCoord;
 
void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_texCoord = a_texCoord;
}
);

const GLchar* ccShader_PathRendering_PositionTexture_frag = SHADER_STRING
(
#ifdef GL_ES
precision lowp float;
#endif
 
uniform sampler2D CC_Texture0;

varying vec2 v_texCoord;
 
void main()
{
    gl_FragColor = texture2D(CC_Texture0, v_texCoord);
}
);

NS_CC_EXT_END
