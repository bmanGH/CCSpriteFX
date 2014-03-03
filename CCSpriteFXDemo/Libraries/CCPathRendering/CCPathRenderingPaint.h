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


class CC_DLL PathRenderingPaint : public cocos2d::Ref, public cocos2d::Clonable {
    
public:
    enum PaintType {
        PAINT_TYPE_COLOR                         = 0x1B00,
        PAINT_TYPE_LINEAR_GRADIENT               = 0x1B01,
        PAINT_TYPE_RADIAL_GRADIENT               = 0x1B02,
//        PAINT_TYPE_PATTERN                       = 0x1B03,
        
        /* 2x3 matrix gradients */
        PAINT_TYPE_LINEAR_2x3_GRADIENT               = 0x1B04,
        PAINT_TYPE_RADIAL_2x3_GRADIENT               = 0x1B05,
    };
    
//    enum PaintTilingMode {
//        PAINT_TILE_FILL                                = 0x1D00,
//        PAINT_TILE_PAD                                 = 0x1D01,
//        PAINT_TILE_REPEAT                              = 0x1D02,
//        PAINT_TILE_REFLECT                             = 0x1D03,
//    };
    
    enum PaintColorRampSpreadMode {
        PAINT_COLOR_RAMP_SPREAD_PAD                    = 0x1C00,
        PAINT_COLOR_RAMP_SPREAD_REPEAT                 = 0x1C01,
        PAINT_COLOR_RAMP_SPREAD_REFLECT                = 0x1C02,
    };
    
    struct color_ramp_stop_t {
        float a[5];
    };
    
protected:
    PaintType               _paintType;
    Color4F                 _paintColor;
    PaintColorRampSpreadMode     _colorRampSpreadMode;
//    bool                    _colorRampPremultiplied;
    float					_paintLinearGradient[4];
    float					_paintRadialGradient[5];
    float					_paint2x3Gradient[6];
//    PaintTilingMode              _patternTilingMode;
    std::vector<color_ramp_stop_t>		_colorRampStops;
    
    Texture2D*		_gradientImage;
    bool            _isDirty;
    
public:
    PathRenderingPaint (PaintType type);
    virtual ~PathRenderingPaint ();
    
    // property
    PaintType getPaintType () {
        return _paintType;
    }
    
    Color4F getPaintColor () {
        return _paintColor;
    }
    
    void setPaintColor (Color4F v) {
        _paintColor = v;
        
        _isDirty = true;
    }
    
    PaintColorRampSpreadMode getColorRampSpreadMode () {
        return _colorRampSpreadMode;
    }
    
    void setColorRampSpreadMode (PaintColorRampSpreadMode colorRampSpreadMode) {
        _colorRampSpreadMode = colorRampSpreadMode;
        
        _isDirty = true;
    }
    
    float* getLinearGradient () {
        return _paintLinearGradient;
    }
    
    void setLinearGradient (float v[4]) {
        for (int i = 0; i < 4; i++) {
            _paintLinearGradient[i] = v[i];
        }
        
        _isDirty = true;
    }
    
    float* getRadialGradient () {
        return _paintRadialGradient;
    }
    
    void setRadialGradient (float v[5]) {
        for (int i = 0; i < 5; i++) {
            _paintRadialGradient[i] = v[i];
        }
        
        _isDirty = true;
    }
    
    float* get2x3Gradient () {
        return _paint2x3Gradient;
    }
    
    void set2x3Gradient (float v[6]) {
        for (int i = 0; i < 6; i++) {
            _paint2x3Gradient[i] = v[i];
        }
        
        _isDirty = true;
    }
    
    const std::vector<color_ramp_stop_t>& getColorRampStops () {
        return _colorRampStops;
    }
    
    void setColorRampStops (float v[], int cnt) {
        _colorRampStops.clear();
        for ( int j = 0; j < cnt / 5; j++ ) {
            color_ramp_stop_t stop;
            for ( int p = 0; p < 5; p++ ) {
                stop.a[p] = v[(j * 5) + p];
            }
            _colorRampStops.push_back( stop );
        }
        
        _isDirty = true;
    }
    
    Texture2D* getGradientImage () {
        return _gradientImage;
    }
    
    // Clonable
    virtual Clonable* clone() const;
    
protected:
    void buildGradientImage (float pathWidth, float pathHeight);
    void buildLinearGradientImage(float pathWidth, float pathHeight);
    void buildRadialGradientImage(float pathWidth, float pathHeight);
    void buildLinear2x3GradientImage(float pathWidth, float pathHeight);
    void buildRadial2x3GradientImage(float pathWidth, float pathHeight);
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(PathRenderingPaint);
    
    friend class PathRenderingPath;
    
};


NS_CC_EXT_END

#endif /* defined(__CCPathRendering__CCPathRenderingPaint__) */
