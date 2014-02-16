//
//  CCPathRenderingPaint.h
//  CCPathRendering
//
//  reference MonkVG:https://github.com/micahpearlman/MonkVG
//
//  Created by bman on 2/9/14.
//
//

#ifndef __CCPathRendering__CCPathRenderingPaint__
#define __CCPathRendering__CCPathRenderingPaint__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>

NS_CC_EXT_BEGIN


class CC_DLL PathRenderingPaint : public cocos2d::Object, public Clonable {
    
public:
    enum PaintType {
        PAINT_TYPE_COLOR                         = 0x1B00,
        PAINT_TYPE_LINEAR_GRADIENT               = 0x1B01,
        PAINT_TYPE_RADIAL_GRADIENT               = 0x1B02,
        PAINT_TYPE_PATTERN                       = 0x1B03,
        
        /* 2x3 matrix gradients */
        PAINT_TYPE_LINEAR_2x3_GRADIENT               = 0x1B04,
        PAINT_TYPE_RADIAL_2x3_GRADIENT               = 0x1B05,
    };
    
protected:
    PaintType _type;
    
public:
    PathRenderingPaint (PaintType type);
    virtual ~PathRenderingPaint ();
    
    // property
    PaintType getPaintType () {
        return _type;
    }
    
    // Clonable
    virtual cocos2d::Clonable* clone () const;
    
protected:
    void buildGradientImage (float width, float height);
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(PathRenderingPaint);
    
    friend class PathRenderingPath;
    
};


NS_CC_EXT_END

#endif /* defined(__CCPathRendering__CCPathRenderingPaint__) */
