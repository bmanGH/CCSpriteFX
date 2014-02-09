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


class CC_DLL PathRenderingPaint {
    
public:
    enum PaintMode {
        PAINT_STROKE_PATH                              = (1 << 0),
        PAINT_FILL_PATH                                = (1 << 1),
    };
    
public:
    PathRenderingPaint ();
    virtual ~PathRenderingPaint ();
    
};


NS_CC_EXT_END

#endif /* defined(__CCPathRendering__CCPathRenderingPaint__) */
