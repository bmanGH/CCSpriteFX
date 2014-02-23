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
    BlendFunc _blendFunc;
    CustomCommand _customRenderCommand;
    
protected:
    GraphicsNode ();
    virtual ~GraphicsNode ();
    virtual bool init ();
    
public:
    GraphicsNode* create ();
    
    const BlendFunc& getBlendFunc() const;
    void setBlendFunc(const BlendFunc &blendFunc);
    const Vector<PathRenderingPath*>& getPaths () {
        return _paths;
    }
    
    virtual Rect getBoundingBox() const override;
    void addPath (PathRenderingPath* path);
    void clear ();
    
    // draw
    virtual void draw () override;
    void render ();
    void drawPath (PathRenderingPath* path);
    
private:
    typedef cocos2d::Node super;
    CC_DISALLOW_COPY_AND_ASSIGN(GraphicsNode);
    
};


NS_CC_EXT_END

#endif /* defined(__CCPathRendering__CCGraphicsNode__) */
