//
//  CCGraphicsNode.h
//  CCPathRendering
//
//  reference HTML5 Canvas API:http://www.w3schools.com/tags/ref_canvas.asp
//
//  Created by bman on 2/8/14.
//
//

#ifndef __CCPathRendering__CCGraphicsNode__
#define __CCPathRendering__CCGraphicsNode__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include "CCPathRenderingPaint.h"
#include "CCPathRenderingPath.h"

NS_CC_EXT_BEGIN

USING_NS_CC;


class CC_DLL GraphicsNode : public cocos2d::Node {
    
protected:
    Vector<PathRenderingPath*> _paths;
    
    GLProgram* _shaderProgramPaintColor;
    GLProgram* _shaderProgramPaintGradient;
    GLint _colorUniform;
    BlendFunc _blendFunc;
    CustomCommand _customRenderCommand;
//    bool _insideBounds;                     // whether or not the sprite was inside bounds the previous frame
    
protected:
    GraphicsNode ();
    virtual ~GraphicsNode ();
    virtual bool init ();
    
//    bool isInsideBounds() const;
    
public:
    static GraphicsNode* create ();
    
    const BlendFunc& getBlendFunc() const;
    void setBlendFunc(const BlendFunc &blendFunc);
    const Vector<PathRenderingPath*>& getPaths () {
        return _paths;
    }
    virtual void setShaderProgram(GLProgram *shaderProgram) override;
    
    virtual Rect getBoundingBox() const override;
    bool addPath (PathRenderingPath* path); // return 'false' if path is NOT stypled, and will not add this path
    void clear ();
    
    // draw
    virtual void draw (Renderer* renderer, const kmMat4 &transform, bool transformUpdated) override;
    void render ();
    void drawPath (PathRenderingPath* path);
    
private:
    typedef cocos2d::Node super;
    CC_DISALLOW_COPY_AND_ASSIGN(GraphicsNode);
    
};


NS_CC_EXT_END

#endif /* defined(__CCPathRendering__CCGraphicsNode__) */
