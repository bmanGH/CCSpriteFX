//
//  CCSpriteFX.cpp
//  CCSpriteFX
//
//  Created by bman on 10/25/13.
//
//

#include "CCSpriteFX.h"
#include "CCColorMatrixShader.h"
#include "CCTextureTransformShader.h"
#include <math.h>

NS_CC_EXT_BEGIN


bool kCCProfilerCategorySpriteFX = false;

SpriteFX* SpriteFX::createWithTexture(Texture2D *texture)
{
    SpriteFX *sprite = new SpriteFX();
    if (sprite && sprite->initWithTexture(texture))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

SpriteFX* SpriteFX::createWithTexture(Texture2D *texture, const Rect& rect)
{
    SpriteFX *sprite = new SpriteFX();
    if (sprite && sprite->initWithTexture(texture, rect))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

SpriteFX* SpriteFX::create(const char *filename)
{
    SpriteFX *sprite = new SpriteFX();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

SpriteFX* SpriteFX::create(const char *filename, const Rect& rect)
{
    SpriteFX *sprite = new SpriteFX();
    if (sprite && sprite->initWithFile(filename, rect))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

SpriteFX* SpriteFX::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
    SpriteFX *sprite = new SpriteFX();
    if (spriteFrame && sprite && sprite->initWithSpriteFrame(spriteFrame))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

SpriteFX* SpriteFX::createWithSpriteFrameName(const char *spriteFrameName)
{
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName);
    CCASSERT(frame != NULL, msg);
#endif
    
    return createWithSpriteFrame(frame);
}

SpriteFX* SpriteFX::create()
{
    SpriteFX *sprite = new SpriteFX();
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

SpriteFX::SpriteFX ()
: _colorMatrixUniformLocation(-1), _needResetColorMatrix(false), _texAnchorOffsetX(0), _texAnchorOffsetY(0), _texOffsetX(0), _texOffsetY(0), _texRotation(0), _texScaleX(1), _texScaleY(1), _texSkewX(0), _texSkewY(0), _texMatrixUniformLocation(-1), _isTexTransformDirty(false) {
    _colorMatrix = CCColorMatrixMakeIdentity();
    kmMat3Identity(&_texMatrix);
}

SpriteFX::~SpriteFX () {
}

void SpriteFX::setTextureWrapRepeat () {
    if (_texture) {
        Texture2D::TexParams texParams;
        if( !_texture->hasMipmaps() )
            texParams.minFilter = GL_LINEAR;
        else
            texParams.minFilter = GL_LINEAR_MIPMAP_NEAREST;
        texParams.magFilter = GL_LINEAR;
        texParams.wrapS = GL_REPEAT;
        texParams.wrapT = GL_REPEAT;
        _texture->setTexParameters(texParams);
        
        this->setTexAnchorOffsetX(0.5);
        this->setTexAnchorOffsetY(0.5);
        this->setTexOffsetX(-0.5);
        this->setTexOffsetY(-0.5);
        this->setTexScaleX(1);
        this->setTexScaleY(1);
        this->setTexSkewX(0);
        this->setTexSkewY(0);
    }
}

void SpriteFX::setTextureWrapMirroredRepeat () {
    if (_texture) {
        Texture2D::TexParams texParams;
        if( !_texture->hasMipmaps() )
            texParams.minFilter = GL_LINEAR;
        else
            texParams.minFilter = GL_LINEAR_MIPMAP_NEAREST;
        texParams.magFilter = GL_LINEAR;
        texParams.wrapS = GL_MIRRORED_REPEAT;
        texParams.wrapT = GL_MIRRORED_REPEAT;
        _texture->setTexParameters(texParams);
        
        this->setTexAnchorOffsetX(0.5);
        this->setTexAnchorOffsetY(0.5);
        this->setTexOffsetX(-0.5);
        this->setTexOffsetY(-0.5);
        this->setTexScaleX(1);
        this->setTexScaleY(1);
        this->setTexSkewX(0);
        this->setTexSkewY(0);
    }
}

void SpriteFX::setTextureWrapClampToEdge () {
    if (_texture) {
        Texture2D::TexParams texParams;
        if( !_texture->hasMipmaps() )
            texParams.minFilter = GL_LINEAR;
        else
            texParams.minFilter = GL_LINEAR_MIPMAP_NEAREST;
        texParams.magFilter = GL_LINEAR;
        texParams.wrapS = GL_CLAMP_TO_EDGE;
        texParams.wrapT = GL_CLAMP_TO_EDGE;
        _texture->setTexParameters(texParams);
        
        this->setTexAnchorOffsetX(0);
        this->setTexAnchorOffsetY(0);
        this->setTexOffsetX(0);
        this->setTexOffsetY(0);
        this->setTexScaleX(1);
        this->setTexScaleY(1);
        this->setTexSkewX(0);
        this->setTexSkewY(0);
    }
}


#pragma mark - Override

void SpriteFX::setTexture(const std::string& fileName) {
    super::setTexture(fileName);
}

void SpriteFX::setTexture(Texture2D *texture) {
    super::setTexture(texture);
    
    if (_texture) {
        this->updateShader();
    }
}

void SpriteFX::draw (Renderer* renderer, const kmMat4 &transform, bool transformUpdated) {
    // Don't do calculate the culling if the transform was not updated
    _insideBounds = transformUpdated ? this->isInsideBounds() : _insideBounds;
    
    if (_insideBounds) {
        _customRenderCommand.init(_globalZOrder);
        _customRenderCommand.func = CC_CALLBACK_0(SpriteFX::render, this);
        Director::getInstance()->getRenderer()->addCommand(&_customRenderCommand);
    }
}

void SpriteFX::render () {
    CC_PROFILER_START_CATEGORY(kCCProfilerCategorySpriteFX, "SpriteFX - draw");
    
    if (_isTexTransformDirty) {
        this->updateTexMatrix();
        _isTexTransformDirty = false;
    }
    
    CC_NODE_DRAW_SETUP();
    // set shader program parameter
    _shaderProgram->setUniformLocationWithMatrix4fv(_colorMatrixUniformLocation,
                                                    _colorMatrix.m,
                                                    1);
    _shaderProgram->setUniformLocationWithMatrix3fv(_texMatrixUniformLocation,
                                                    _texMatrix.mat,
                                                    1);
    
    GL::blendFunc( _blendFunc.src, _blendFunc.dst );
    
    GL::bindTexture2D( _texture->getName() );
    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
    
#define kQuadSize sizeof(_quad.bl)
#ifdef EMSCRIPTEN
    long offset = 0;
    setGLBufferData(&_quad, 4 * kQuadSize, 0);
#else
    long offset = (long)&_quad;
#endif // EMSCRIPTEN
    
    // vertex
    int diff = offsetof( V3F_C4B_T2F, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
    if (_texture != NULL)
    {
        // texCoods
        diff = offsetof( V3F_C4B_T2F, texCoords);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    }
    
    // color
    diff = offsetof( V3F_C4B_T2F, colors);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    CHECK_GL_ERROR_DEBUG();
    
#if CC_SPRITE_DEBUG_DRAW == 1
    // draw bounding box
    Point vertices[4] = {
        Point( _quad.bl.vertices.x, _quad.bl.vertices.y ),
        Point( _quad.br.vertices.x, _quad.br.vertices.y ),
        Point( _quad.tr.vertices.x, _quad.tr.vertices.y ),
        Point( _quad.tl.vertices.x, _quad.tl.vertices.y ),
    };
    DrawPrimitives::drawPoly(vertices, 4, true);
#elif CC_SPRITE_DEBUG_DRAW == 2
    // draw texture box
    Size s = this->getTextureRect().size;
    Point offsetPix = this->getOffsetPosition();
    Point vertices[4] = {
        Point(offsetPix.x,offsetPix.y), Point(offsetPix.x+s.width,offsetPix.y),
        Point(offsetPix.x+s.width,offsetPix.y+s.height), Point(offsetPix.x,offsetPix.y+s.height)
    };
    DrawPrimitives::drawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW
    
    CC_INCREMENT_GL_DRAWS(1);
    
    CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySpriteColorMatrix, "SpriteFX - draw");
    
    if (_needResetColorMatrix)
        _colorMatrix = CCColorMatrixMakeIdentity();
}


#pragma mark - Private

void SpriteFX::updateShader () {
    if (_texture->hasPremultipliedAlpha()) {
        GLProgram* glProgram = ShaderCache::getInstance()->getProgram(kCCShader_PositionTextureColorColorMatrixPremultipliedAlpha);
        if (glProgram == nullptr) {
            glProgram = new GLProgram();
            glProgram->initWithByteArrays(ccShader_PositionTextureColorTextureTransform_vert,
                                          ccShader_PositionTextureColorColorMatrixPremultipliedAlpha_frag);
            
            glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
            glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
            
            glProgram->link();
            glProgram->updateUniforms();
            
            CHECK_GL_ERROR_DEBUG();
            
            ShaderCache::getInstance()->addProgram(glProgram, kCCShader_PositionTextureColorColorMatrixPremultipliedAlpha);
        }
        else {
            glProgram->retain();
        }
        this->setShaderProgram(glProgram);
        
        _colorMatrixUniformLocation = glProgram->getUniformLocationForName("u_colorMatrix");
        _texMatrixUniformLocation = glProgram->getUniformLocationForName("u_texMatrix");
        
        glProgram->release();
    }
    else {
        GLProgram* glProgram = ShaderCache::getInstance()->getProgram(kCCShader_PositionTextureColorColorMatrix);
        if (glProgram == nullptr) {
            glProgram = new GLProgram();
            glProgram->initWithByteArrays(ccShader_PositionTextureColorTextureTransform_vert,
                                          ccShader_PositionTextureColorColorMatrix_frag);
            
            glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
            glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
            
            glProgram->link();
            glProgram->updateUniforms();
            
            CHECK_GL_ERROR_DEBUG();
            
            ShaderCache::getInstance()->addProgram(glProgram, kCCShader_PositionTextureColorColorMatrix);
        }
        else {
            glProgram->retain();
        }
        this->setShaderProgram(glProgram);
        
        _colorMatrixUniformLocation = glProgram->getUniformLocationForName("u_colorMatrix");
        _texMatrixUniformLocation = glProgram->getUniformLocationForName("u_texMatrix");
        
        glProgram->release();
    }
}

void SpriteFX::updateTexMatrix () {
    AffineTransform texTransform;
    
    // Translate values
    float x = _texOffsetX;
    float y = _texOffsetY;
    
    // Rotation values
    // Change rotation code to handle X and Y
    // If we skew with the exact same value for both x and y then we're simply just rotating
    float c = 1, s = 0;
    if (_texRotation)
    {
        float radians = -CC_DEGREES_TO_RADIANS(_texRotation);
        c = cosf(radians);
        s = sinf(radians);
    }
    
    bool needsSkewMatrix = ( _texSkewX || _texSkewY );
    
    // optimization:
    // inline anchor point calculation if skew is not needed
    // Adjusted transform calculation for rotational skew
    if (!needsSkewMatrix && (_texAnchorOffsetX || _texAnchorOffsetY))
    {
        x += c * -_texAnchorOffsetX * _texScaleX + -s * -_texAnchorOffsetY * _texScaleY;
        y += s * -_texAnchorOffsetX * _texScaleX +  c * -_texAnchorOffsetY * _texScaleY;
    }
    
    // Build Transform Matrix
    // Adjusted transform calculation for rotational skew
    texTransform = AffineTransformMake( c * _texScaleX,  s * _texScaleX,
                                       -s * _texScaleY, c * _texScaleY,
                                       x, y );
    
    // If skew is needed, apply skew
    if (needsSkewMatrix)
    {
        AffineTransform skewMatrix = AffineTransformMake(1.0f, tanf(CC_DEGREES_TO_RADIANS(_texSkewY)),
                                                         tanf(CC_DEGREES_TO_RADIANS(_texSkewX)), 1.0f,
                                                         0.0f, 0.0f );
        texTransform = AffineTransformConcat(skewMatrix, texTransform);
        
        // adjust anchor point
        if (_texAnchorOffsetX || _texAnchorOffsetY)
        {
            texTransform = AffineTransformTranslate(texTransform, -_texAnchorOffsetX, -_texAnchorOffsetY);
        }
    }
    
    float* m = _texMatrix.mat;
    
    // | m[0] m[3] m[6] |     | m11 m21 m31 |     | a c tx |
    // | m[1] m[4] m[7] |     | m12 m22 m32 |     | b d ty |
    // | m[2] m[5] m[8] | <=> | m13 m23 m33 | <=> | 0 0 1  |
    
    m[2] = m[5] = 0.0f;
    m[8] = 1.0f;
    m[0] = texTransform.a; m[3] = texTransform.c; m[6] = texTransform.tx;
    m[1] = texTransform.b; m[4] = texTransform.d; m[7] = texTransform.ty;
}


#pragma mark - ColorMatrixProtocol

void SpriteFX::setColorMatrix (const ColorMatrix4x4& colorMatrix) {
    _colorMatrix = colorMatrix;
}

ColorMatrix4x4 SpriteFX::getColorMatrix () {
    return _colorMatrix;
}

void SpriteFX::concatColorMatrix (const ColorMatrix4x4& colorMatrix) {
    _colorMatrix = CCColorMatrixConcat(&colorMatrix, &_colorMatrix);
}

void SpriteFX::setNeedResetColorMatrixAfterDraw (bool value) {
    _needResetColorMatrix = value;
}

bool SpriteFX::isNeedResetColorMatrixAfterDraw () {
    return _needResetColorMatrix;
}


#pragma mark - TextureTransformProtocol

float SpriteFX::getTexAnchorOffsetX () {
    return _texAnchorOffsetX;
}

void SpriteFX::setTexAnchorOffsetX (float value) {
    _texAnchorOffsetX = value;
    _isTexTransformDirty = true;
}

float SpriteFX::getTexAnchorOffsetY () {
    return _texAnchorOffsetY;
}

void SpriteFX::setTexAnchorOffsetY (float value) {
    _texAnchorOffsetY = value;
    _isTexTransformDirty = true;
}

float SpriteFX::getTexOffsetX () {
    return _texOffsetX;
}

void SpriteFX::setTexOffsetX (float value) {
    _texOffsetX = value;
    _isTexTransformDirty = true;
}

float SpriteFX::getTexOffsetY () {
    return _texOffsetY;
}

void SpriteFX::setTexOffsetY (float value) {
    _texOffsetY = value;
    _isTexTransformDirty = true;
}

float SpriteFX::getTexRotation () {
    return _texRotation;
}

void SpriteFX::setTexRotation (float value) {
    _texRotation = value;
    _isTexTransformDirty = true;
}

float SpriteFX::getTexScaleX () {
    return _texScaleX;
}

void SpriteFX::setTexScaleX (float value) {
    _texScaleX = value;
    _isTexTransformDirty = true;
}

float SpriteFX::getTexScaleY () {
    return _texScaleY;
}

void SpriteFX::setTexScaleY (float value) {
    _texScaleY = value;
    _isTexTransformDirty = true;
}

float SpriteFX::getTexSkewX () {
    return _texSkewX;
}

void SpriteFX::setTexSkewX (float value) {
    _texSkewX = value;
    _isTexTransformDirty = true;
}

float SpriteFX::getTexSkewY () {
    return _texSkewY;
}

void SpriteFX::setTexSkewY (float value) {
    _texSkewY = value;
    _isTexTransformDirty = true;
}


NS_CC_EXT_END
