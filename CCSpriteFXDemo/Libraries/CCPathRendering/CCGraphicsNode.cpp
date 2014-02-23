//
//  CCGraphicsNode.cpp
//  CCSpriteFXDemo
//
//  Created by bman on 2/8/14.
//
//

#include "CCGraphicsNode.h"

NS_CC_EXT_BEGIN


bool kCCProfilerCategoryGraphicsNode = false;
#define CC_GRAPHICS_NODE_DEBUG_DRAW     (0)

GraphicsNode::GraphicsNode ()
: _blendFunc(BlendFunc::ALPHA_PREMULTIPLIED)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    auto listener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom* event){
        for (PathRenderingPath* path : _paths) {
            path->setIsDirty(true);
        }
    });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
}

GraphicsNode::~GraphicsNode ()
{
}

bool GraphicsNode::init () {
    if (super::init()) {
        return true;
    }
    return false;
}

GraphicsNode* GraphicsNode::create () {
    GraphicsNode *node = new GraphicsNode();
    if (node && node->init())
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

const BlendFunc& GraphicsNode::getBlendFunc() const {
    return _blendFunc;
}

void GraphicsNode::setBlendFunc(const BlendFunc &blendFunc) {
    _blendFunc = blendFunc;
}

Rect GraphicsNode::getBoundingBox() const {
    Rect ret;
    for (PathRenderingPath* path : _paths) {
        //TODO
    }
    return ret;
}

void GraphicsNode::addPath (PathRenderingPath* path) {
    _paths.pushBack(path);
}

void GraphicsNode::clear () {
    _paths.clear();
}

#pragma mark - draw

void GraphicsNode::draw () {
    _customRenderCommand.init(_globalZOrder);
    _customRenderCommand.func = CC_CALLBACK_0(GraphicsNode::render, this);
    Director::getInstance()->getRenderer()->addCommand(&_customRenderCommand);
}

void GraphicsNode::render () {
    CC_PROFILER_START_CATEGORY(kCCProfilerCategoryGraphicsNode, "GraphicsNode - draw");
    
    for (PathRenderingPath* path : _paths) {
        path->buildVBOIfDirty();
        this->drawPath(path);
    }
    
#if CC_GRAPHICS_NODE_DEBUG_DRAW == 1
    // draw bounding box
    Rect bbox = this->getBoundingBox();
    Point vertices[4]={
        Point(bbox.origin.x, bbox.origin.y + bbox.size.height), // top-left
        Point(bbox.origin.x, bbox.origin.y), // bottom-left
        Point(bbox.origin.x + bbox.size.width, bbox.origin.y), // bottom-right
        Point(bbox.origin.x + bbox.size.width, bbox.origin.y + bbox.size.height), // top-right
    };
    DrawPrimitives::drawPoly(vertices, 4, true);
#endif
    
    CC_PROFILER_STOP_CATEGORY(kCCProfilerCategoryGraphicsNode, "SpriteFX - draw");
}

void GraphicsNode::drawPath (PathRenderingPath* path) {
    // draw fill
    if (path->_numberFillVertices > 0 && path->_fillPaintForPath) {
        if (path->_fillPaintForPath->getPaintType() == PathRenderingPaint::PAINT_TYPE_COLOR ) {
            setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR));
            CC_NODE_DRAW_SETUP();
            
            GL::blendFunc( _blendFunc.src, _blendFunc.dst );
            GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
            
            glBindBuffer(GL_ARRAY_BUFFER, path->_fillVBO);
            // vertex
            glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION,
                                  2,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  sizeof(PathRenderingPath::v2_t),
                                  0);
            
//            // color
//            glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
            
            glDrawArrays(GL_TRIANGLES, 0, path->_numberFillVertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        // TBD: PAINT_TYPE_PATTERN is not support
//        else if (path->_fillPaintForPath->getPaintType() == PathRenderingPaint::PAINT_TYPE_PATTERN) {
//        }
        else {
            setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR));
            CC_NODE_DRAW_SETUP();
            
            GL::blendFunc( _blendFunc.src, _blendFunc.dst );
            GL::bindTexture2D(path->_fillPaintForPath->getGradientImage()->getName());
            GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
            
            glBindBuffer(GL_ARRAY_BUFFER, path->_fillVBO);
            // vertex
            glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION,
                                  2,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  sizeof(PathRenderingPath::textured_vertex_t),
                                  (GLvoid*)offsetof(PathRenderingPath::textured_vertex_t, v));
            
//            // color
//            glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
            
            // texcood
            glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS,
                                  2,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  sizeof(PathRenderingPath::textured_vertex_t),
                                  (GLvoid*)offsetof(PathRenderingPath::textured_vertex_t, uv));
            
            glDrawArrays(GL_TRIANGLES, 0, path->_numberFillVertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
    
    CHECK_GL_ERROR_DEBUG();
    CC_INCREMENT_GL_DRAWS(1);
    
    // draw stroke
    if (path->_numberStrokeVertices > 0 && path->_strokePaintForPath) {
        if (path->_strokePaintForPath->getPaintType() == PathRenderingPaint::PAINT_TYPE_COLOR ) {
            setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR));
            CC_NODE_DRAW_SETUP();
            
            GL::blendFunc( _blendFunc.src, _blendFunc.dst );
            GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
            
            glBindBuffer(GL_ARRAY_BUFFER, path->_strokeVBO);
            // vertex
            glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION,
                                  2,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  sizeof(PathRenderingPath::v2_t),
                                  0);
            
//            // color
//            glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
            
            glDrawArrays(GL_TRIANGLE_STRIP, 0, path->_numberStrokeVertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        // TBD: PAINT_TYPE_PATTERN, PAINT_TYPE_LINEAR_GRADIENT, PAINT_TYPE_RADIAL_GRADIENT,
        //      PAINT_TYPE_LINEAR_2x3_GRADIENT, PAINT_TYPE_RADIAL_2x3_GRADIENT is not support
//        else if (path->_strokePaintForPath->getPaintType() == PathRenderingPaint::PAINT_TYPE_PATTERN) {
//        }
//        else {
//        }
    }
    
    CHECK_GL_ERROR_DEBUG();
    CC_INCREMENT_GL_DRAWS(1);
    
#if CC_GRAPHICS_NODE_DEBUG_DRAW == 2
    // draw path bounding box
    Rect bbox = path->getBounds();
    Point vertices[4]={
        Point(bbox.origin.x, bbox.origin.y + bbox.size.height), // top-left
        Point(bbox.origin.x, bbox.origin.y), // bottom-left
        Point(bbox.origin.x + bbox.size.width, bbox.origin.y), // bottom-right
        Point(bbox.origin.x + bbox.size.width, bbox.origin.y + bbox.size.height), // top-right
    };
    DrawPrimitives::drawPoly(vertices, 4, true);
#endif
}


NS_CC_EXT_END
