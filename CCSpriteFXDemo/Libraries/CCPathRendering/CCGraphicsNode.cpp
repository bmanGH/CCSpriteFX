//
//  CCGraphicsNode.cpp
//  CCSpriteFXDemo
//
//  Created by bman on 2/8/14.
//
//

#include "CCGraphicsNode.h"

NS_CC_EXT_BEGIN


GraphicsNode::GraphicsNode ()
{
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
    for (PathRenderingPath* path : _paths) {
        path->buildVBOIfDirty();
        this->drawPath(path);
    }
}

void GraphicsNode::drawPath (PathRenderingPath* path) {
    
}


NS_CC_EXT_END
