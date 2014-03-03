//
//  CCPathRenderingPath.h
//  CCPathRendering
//
//  reference MonkVG:https://github.com/micahpearlman/MonkVG
//  reference Chromium:http://src.chromium.org/svn/branches/WebKit/472/WebCore/platform/graphics/openvg/PathOpenVG.cpp
//
//  Created by bman on 2/9/14.
//
//

#ifndef __CCPathRendering__CCPathRenderingPath__
#define __CCPathRendering__CCPathRenderingPath__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "glu.h"
#include <vector>
#include "CCPathRenderingPaint.h"

NS_CC_EXT_BEGIN


/**
 * @note "coords" means the count of path segment's params, "path command" same as path segment
 */
class CC_DLL PathRenderingPath : public cocos2d::Ref, public cocos2d::Clonable {
    
public:
    enum PathSegment : unsigned int {
        PATH_CLOSE_PATH                               = ( 0 << 1),
        PATH_MOVE_TO                                  = ( 1 << 1),
        PATH_LINE_TO                                  = ( 2 << 1),
        PATH_HLINE_TO                                 = ( 3 << 1),
        PATH_VLINE_TO                                 = ( 4 << 1),
        PATH_QUAD_TO                                  = ( 5 << 1),
        PATH_CUBIC_TO                                 = ( 6 << 1),
        PATH_SQUAD_TO                                 = ( 7 << 1),
        PATH_SCUBIC_TO                                = ( 8 << 1),
        PATH_SCCWARC_TO                               = ( 9 << 1),
        PATH_SCWARC_TO                                = (10 << 1),
        PATH_LCCWARC_TO                               = (11 << 1),
        PATH_LCWARC_TO                                = (12 << 1),
    };
    
    enum ArcType {
        ARC_OPEN                            =  0,
        ARC_CHORD                           =  1,
        ARC_PIE                             =  2,
    };
    
    enum PathFillRule {
        FILL_RULE_EVEN_ODD                                 = 0x1900,
        FILL_RULE_NON_ZERO                                 = 0x1901,
    };
    
    struct v2_t {
        GLfloat x, y;
        
        void print() const {
            printf("(%f, %f)\n", x, y);
        }
    };
    
    struct v3_t {
        GLdouble x, y, z;
        
        v3_t( const v2_t& v ) : x(v.x), y(v.y), z(0) {}
        
        v3_t() : x(0), y(0), z(0) {}
        
        void print() const {
            printf("(%f, %f, %f)\n", x, y, z);
        }
    };
    
    struct textured_vertex_t {
        GLfloat		v[2];
        GLfloat		uv[2];
    };
    
protected:
    // 2d
    float               _scale;
    float               _bias;
    int                 _numSegments;
    int                 _numCoords;
    int                 _tessellationIterations;
    std::vector< unsigned int >    _segments;
    std::vector< float >            _fcoords;
    float				_minX;
    float				_minY;
    float				_height;
    float				_width;
    PathFillRule        _fillRule;
    float               _lineWidth;
    PathRenderingPaint*     _fillPaintForPath;
    PathRenderingPaint*     _strokePaintForPath;
    Point               _beginPoint;
    Point               _currentPoint;
    bool                _isStyled;
    
    std::vector<v2_t>       _fillVertices;
    std::vector<v2_t>		_strokeVertices;
    
    // 3d
    GLenum                  _primType;
    GLenum                  _bufferMode;
    GLuint                  _fillVBO;
    GLuint                  _strokeVBO;
    int                     _numberFillVertices;
    int                     _numberStrokeVertices;
    bool                    _isFillDirty;
    bool                    _isStrokeDirty;
    
    // use in gluTess callback
    GLUtesselator*          _fillTesseleator;
    std::list<v3_t>			_tessVertices;
    GLdouble                startVertex_[2];
	GLdouble                lastVertex_[2];
	int                     vertexCount_;
    
public:
    PathRenderingPath(float scale = 1,
                      float bias = 0,
                      int tessellationIterations = 50,
                      GLenum bufferMode = GL_STATIC_DRAW);
    virtual ~PathRenderingPath();
    
    void clear();
    bool isStyled () { return _isStyled; }
    Point getBeginPoint () { return _beginPoint; }
    Point getCurrentPoint () { return _currentPoint; }
    
    // path command
    void moveTo (const Point& to);
    void lineTo (const Point& to);
    void quadraticBezierCurveTo (const Point& control, const Point& to);
    void cubicBezierCurveTo (const Point& control1, const Point& control2, const Point& to);
    void arcTo (const Size& arcSize, const float rot, const Point& to); // CCW
    void arcTo (const Point& from, const Point& to, float radius);
    void close ();
    
    // Shape
    void line (const Point& from, const Point& to);
    void polygon (const std::vector<Point>& points, bool closed); // points size should >= 2
    void rect (const Point& origin, const Size& size);
    void roundRect (const Point& origin, const Size& size, const Size& arcSize);
    void ellipse (const Point& center, const Size& size);
    void arc (const Point& center, const Size& size, float startAngle, float angleExtent, PathRenderingPath::ArcType arcType);
    void triangle (const Point &p1, const Point &p2, const Point &p3);
    void quadraticBezierCurve(const Point& from, const Point& control, const Point& to);
    void cubicBezierCurve(const Point& from, const Point& control1, const Point& control2, const Point& to);
    
    void fill (PathRenderingPaint* paint, PathFillRule fillRule);
    void stroke (PathRenderingPaint* paint, float lineWidth);
    void fillAndStroke (PathRenderingPaint* fillPaint, PathFillRule fillRule,
                        PathRenderingPaint* strokePaint, float lineWidth);
    
    // property
    float getScale () {
        return _scale;
    }
    
    void setScale (float v) {
        _scale = v;
    }
    
    float getBias () {
        return _bias;
    }
    
    void setBias (float v) {
        _bias = v;
    }
    
    int getNumSegments() {
        return _numSegments;
    }
    
    int getNumCoords() {
        return _numCoords;
    }
    
    int getTessellationIterations () {
        return _tessellationIterations;
    }
    
    void setTessellationIterations (int v) {
        _tessellationIterations = v;
    }
    
    bool getIsDirty() {
        return _isFillDirty || _isStrokeDirty;
    }
    void setIsDirty( bool b ) {
        _isFillDirty = b;
        _isStrokeDirty = b;
    }
    
    float getMinX() {
        return _minX;
    }
    float getMinY() {
        return _minY;
    }
    float getWidth() {
        return _width;
    }
    float getHeight() {
        return _height;
    }
    
    /**
     * @note only care about the fill bounds, NOT the fill + stroke
     */
    cocos2d::Rect getBounds () {
        return cocos2d::Rect(_minX, _minY, _width, _height);
    }
    
    GLenum getPrimType() {
        return _primType;
    }
    void setPrimType( GLenum t ) {
        _primType = t;
    }
    
    GLenum getBufferMode () {
        return _bufferMode;
    }
    void setBufferMode ( GLenum t ) {
        _bufferMode = t;
    }
    
    // Clonable
    virtual Clonable* clone() const;
    
protected:
    // tesseleator callbacks
    static GLvoid tessBegin( GLenum type, GLvoid* user );
    static GLvoid tessEnd( GLvoid* user );
    static GLvoid tessVertex( GLvoid *vertex, GLvoid* user );
    static GLvoid tessCombine( GLdouble coords[3], void *data[4],
                            GLfloat weight[4], void **outData,
                            void *polygonData );
    static GLvoid tessError( GLenum errorCode );
    
    // internal methods
    void addVertex( GLdouble* v );
    GLdouble* tessVerticesBackPtr();
    void addTessVertex( const v3_t& v );
    
    void buildFatLineSegment( std::vector<v2_t>& vertices, const v2_t& p0, const v2_t& p1, const float radius );
    void appendData( const int numSegments, const unsigned int* pathSegments, const float* pathData ) ;
    int32_t segmentToNumCoordinates(PathSegment segment); // get count of path segment's params
    
    void buildVBOIfDirty ();
    void buildFillVBO ();
    void buildStrokeVBO ();
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(PathRenderingPath);
    
    friend class GraphicsNode;
    
};


NS_CC_EXT_END

#endif /* defined(__CCPathRendering__CCPathRenderingPath__) */
