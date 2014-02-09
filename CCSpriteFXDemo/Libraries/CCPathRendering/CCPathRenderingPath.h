//
//  CCPathRenderingPath.h
//  CCPathRendering
//
//  reference MonkVG:https://github.com/micahpearlman/MonkVG
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
 * @note "Coords" means the count of path segment's params
 */
class CC_DLL PathRenderingPath {
    
public:
    enum PathSegment {
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
    
    enum PathCapabilities {
        PATH_CAPABILITY_APPEND_FROM              = (1 <<  0),
        PATH_CAPABILITY_APPEND_TO                = (1 <<  1),
        PATH_CAPABILITY_MODIFY                   = (1 <<  2),
        PATH_CAPABILITY_TRANSFORM_FROM           = (1 <<  3),
        PATH_CAPABILITY_TRANSFORM_TO             = (1 <<  4),
        PATH_CAPABILITY_INTERPOLATE_FROM         = (1 <<  5),
        PATH_CAPABILITY_INTERPOLATE_TO           = (1 <<  6),
        PATH_CAPABILITY_PATH_LENGTH              = (1 <<  7),
        PATH_CAPABILITY_POINT_ALONG_PATH         = (1 <<  8),
        PATH_CAPABILITY_TANGENT_ALONG_PATH       = (1 <<  9),
        PATH_CAPABILITY_PATH_BOUNDS              = (1 << 10),
        PATH_CAPABILITY_PATH_TRANSFORMED_BOUNDS  = (1 << 11),
        PATH_CAPABILITY_ALL                      = (1 << 12) - 1,
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
    int                 _format;
    float				_scale;
    float				_bias;
    int                 _numSegments;
    int                 _numCoords;
    unsigned int			_capabilities;
    std::vector< unsigned char >    _segments;
    std::vector< float >            _fcoords;
    bool                            _isFillDirty;
    bool                            _isStrokeDirty;
    float				_minX;
    float				_minY;
    float				_height;
    float				_width;
    
    // 3d
    GLUtesselator*          _fillTesseleator;
    std::vector<GLfloat>	_vertices;
    std::vector<v2_t>		_strokeVertices;
    std::list<v3_t>			_tessVertices;
    GLenum                  _primType;
    GLuint                  _fillVBO;
    GLuint                  _strokeVBO;
    int                     _numberFillVertices;
    int                     _numberStrokeVertices;
    PathRenderingPaint*     _fillPaintForPath;
    PathRenderingPaint*     _strokePaintForPath;
    
public:
    PathRenderingPath( int pathFormat,
                      float scale,
                      float bias,
                      int segmentCapacityHint,
                      int coordCapacityHint,
                      unsigned int capabilities );
    virtual ~PathRenderingPath();
    
    void draw( unsigned int paintModes );
    
    void clear();
    
    void addVertex( GLdouble* v );
    
    GLdouble* tessVerticesBackPtr();
    
    void addTessVertex( const v3_t& v );
    
    // path command
    void moveTo (const Point& to);
    void lineTo (const Point& to);
    void quadraticBezierCurveTo (const Point& control, const Point& to, unsigned int segments = 50);
    void cubicBezierCurveTo (const Point& control1, const Point& control2, const Point& to, unsigned int segments = 50);
    void arc (const Point& to);
    void arcTo (const Point& to);
    void fill (PathRenderingPaint* paint);
    void stroke (PathRenderingPaint* paint);
    
    // Shape
    void line (const Point& from, const Point& to);
    void polygon (const std::vector<Point>& points);
    void rect (const Point& origin, const Size& size);
    void roundRect (const Point& origin, const Size& size, const Size& arcSize);
    void ellipse (const Point& center, const Size& size);
    void arc (const Point& center, const Size& size, float startAngle, float angleExtent, PathRenderingPath::ArcType arcType);
    void triangle (const Point &p1, const Point &p2, const Point &p3);
    void quadraticBezierCurve(const Point& from, const Point& control, const Point& to, unsigned int segments = 50);
    void cubicBezierCurve(const Point& from, const Point& control1, const Point& control2, const Point& to, unsigned int segments = 50);
    
    // property
    int getFormat() const {
        return _format;
    }
    void setFormat( const int f ) {
        _format = f;
    }
    
    float getScale() const {
        return _scale;
    }
    void setScale( const float s ) {
        _scale = s;
    }
    
    float getBias() const {
        return _bias;
    }
    void setBias( const float b ) {
        _bias = b;
    }
    
    int getNumSegments() const {
        return _numSegments;
    }
    void setNumSegments( const int ns ) {
        _numSegments = ns;
    }
    
    int getNumCoords() const {
        return _numCoords;
    }
    void setNumCoords( const int nc ) {
        _numCoords = nc;
    }
    
    unsigned int getCapabilities( ) const {
        return _capabilities;
    }
    void setCapabilities( const unsigned int c ) {
        _capabilities = c;
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
    
    GLenum primType() {
        return _primType;
    }
    void setPrimType( GLenum t ) {
        _primType = t;
    }
    
protected:
    // tesseleator callbacks
    static void tessBegin( GLenum type, GLvoid* user );
    static void tessEnd( GLvoid* user );
    static void tessVertex( GLvoid *vertex, GLvoid* user );
    static void tessCombine( GLdouble coords[3], void *data[4],
                            GLfloat weight[4], void **outData,
                            void *polygonData );
    static void tessError( GLenum errorCode );
    void endOfTesselation( unsigned int paintModes );
    
    // utility methods
    void buildFill();
    void buildStroke();
    void buildFatLineSegment( std::vector<v2_t>& vertices, const v2_t& p0, const v2_t& p1, const float radius );
    
    void appendData( const int numSegments, const unsigned char* pathSegments, const void* pathData ) ;
    int32_t segmentToNumCoordinates(PathSegment segment);
    
};


NS_CC_EXT_END

#endif /* defined(__CCPathRendering__CCPathRenderingPath__) */
