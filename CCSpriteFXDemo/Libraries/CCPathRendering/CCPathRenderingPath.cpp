//
//  CCPathRenderingPath.cpp
//  CCSpriteFXDemo
//
//  Created by bman on 2/9/14.
//
//

#include "CCPathRenderingPath.h"
#include <cassert>

NS_CC_EXT_BEGIN


static inline float calcCubicBezier1d( float x0, float x1, float x2, float x3, float t ) {
    // see openvg 1.0 spec section 8.3.2 Cubic Bezier Curves
    float oneT = 1.0f - t;
    float x =		x0 * (oneT * oneT * oneT)
    +	3.0f * x1 * (oneT * oneT) * t
    +	3.0f * x2 * oneT * (t * t)
    +	x3 * (t * t * t);
    return x;
}

static inline float calcQuadBezier1d( float start, float control, float end, float time ) {
    float inverseTime = 1.0f - time;
    return (powf(inverseTime, 2.0f) * start) + (2.0f * inverseTime * time * control) + (powf(time, 2.0f) * end);
}

// Given: Points (x0, y0) and (x1, y1)
// Return: TRUE if a solution exists, FALSE otherwise
// Circle centers are written to (cx0, cy0) and (cx1, cy1)
static inline bool findUnitCircles(float x0, float y0, float x1, float y1,
                                 float *cx0, float *cy0, float *cx1, float *cy1) {
    
    // Compute differences and averages
    float dx = x0 - x1;
    float dy = y0 - y1;
    float xm = (x0 + x1)/2;
    float ym = (y0 + y1)/2;
    float dsq, disc, s, sdx, sdy;
    // Solve for intersecting unit circles
    dsq = dx*dx + dy*dy;
    if (dsq == 0.0)
        return false; // Points are coincident
    disc = 1.0f/dsq - 1.0f/4.0f;
    if (disc < 0.0)
        return false; // Points are too far apart
    
    s = sqrt(disc);
    sdx = s*dx;
    sdy = s*dy;
    *cx0 = xm + sdy;
    *cy0 = ym - sdx;
    *cx1 = xm - sdy;
    *cy1 = ym + sdx;
    
    return true;
}

// Ellipse parameters rh, rv, rot (in degrees), endpoints (x0, y0) and (x1, y1) TRUE if a solution exists, FALSE otherwise.
// Ellipse centers are written to (cx0, cy0) and (cx1, cy1)
static inline bool findEllipses(float rh, float rv, float rot,
                              float x0, float y0, float x1, float y1,
                              float *cx0, float *cy0, float *cx1, float *cy1) {
    float COS, SIN, x0p, y0p, x1p, y1p, pcx0, pcy0, pcx1, pcy1;
    // Convert rotation angle from degrees to radians
    rot *= M_PI/180.0;
    // Pre-compute rotation matrix entries
    COS = cos(rot);
    SIN = sin(rot);
    // Transform (x0, y0) and (x1, y1) into unit space
    // using (inverse) rotate, followed by (inverse) scale
    x0p = (x0*COS + y0*SIN)/rh;
    y0p = (-x0*SIN + y0*COS)/rv;
    x1p = (x1*COS + y1*SIN)/rh;
    y1p = (-x1*SIN + y1*COS)/rv;
    if (!findUnitCircles(x0p, y0p, x1p, y1p, &pcx0, &pcy0, &pcx1, &pcy1)) {
        return false;
    }
    // Transform back to original coordinate space
    // using (forward) scale followed by (forward) rotate
    pcx0 *= rh;
    pcy0 *= rv;
    pcx1 *= rh;
    pcy1 *= rv;
    *cx0 = pcx0*COS - pcy0*SIN;
    *cy0 = pcx0*SIN + pcy0*COS; 
    *cx1 = pcx1*COS - pcy1*SIN; 
    *cy1 = pcx1*SIN + pcy1*COS;
    
    return true;
}


PathRenderingPath::PathRenderingPath( int pathFormat,
                                     float scale,
                                     float bias,
                                     int segmentCapacityHint,
                                     int coordCapacityHint,
                                     unsigned int capabilities )
: _format(pathFormat),
_scale(scale),
_bias(bias),
_numSegments(segmentCapacityHint),
_numCoords(coordCapacityHint),
_capabilities(capabilities),
_fcoords(coordCapacityHint),
_isFillDirty(true),
_isStrokeDirty(true),
_minX(MAXFLOAT),
_minY(MAXFLOAT),
_height(-MAXFLOAT),
_width(-MAXFLOAT),
_fillTesseleator(0),
_primType(0),
_fillVBO(-1),
_strokeVBO(-1),
_numberFillVertices(0),
_numberStrokeVertices(0),
_fillPaintForPath(nullptr),
_strokePaintForPath(nullptr)
{
}

PathRenderingPath::~PathRenderingPath()
{
    // delete vbo
    if ( _strokeVBO != -1 )
        glDeleteBuffers( 1, &_strokeVBO );
    if ( _fillVBO != -1 )
        glDeleteBuffers( 1, &_fillVBO );
    
    delete _fillTesseleator;
    delete _fillPaintForPath;
    delete _strokePaintForPath;
}

void PathRenderingPath::draw( unsigned int paintModes ) {
    
}

void PathRenderingPath::clear() {
    _segments.clear();
    _numSegments = 0;
    _fcoords.clear();
    _numCoords = 0;
    
    _vertices.clear();
    // delete vbo
    if ( _strokeVBO != -1 ) {
        glDeleteBuffers( 1, &_strokeVBO );
        _strokeVBO = -1;
    }
    if ( _fillVBO != -1 ) {
        glDeleteBuffers( 1, &_fillVBO );
        _fillVBO = -1;
    }
}

void PathRenderingPath::addVertex( GLdouble* v ) {
    // calculate the bounds
    if ( v[0] < _minX ) {
        _minX = (float)v[0];
    }
    if ( v[0] > _width ) {
        _width = (float)v[0];
    }
    if ( v[1] < _minY ) {
        _minY = (float)v[1];
    }
    if ( v[1] > _height ) {
        _height = (float)v[1];
    }
    
    _vertices.push_back( (float)v[0] );
    _vertices.push_back( (float)v[1] );
}

GLdouble* PathRenderingPath::tessVerticesBackPtr() {
    return &(_tessVertices.back().x);
}

void PathRenderingPath::addTessVertex( const v3_t& v ) {
    _tessVertices.push_back( v );
}


#pragma mark - path command

void PathRenderingPath::moveTo (const Point& to) {
    
}

void PathRenderingPath::lineTo (const Point& to) {
    
}

void PathRenderingPath::quadraticBezierCurveTo (const Point& control, const Point& to, unsigned int segments) {
    
}

void PathRenderingPath::cubicBezierCurveTo (const Point& control1, const Point& control2, const Point& to, unsigned int segments) {
    
}

void PathRenderingPath::arc (const Point& to) {
    
}

void PathRenderingPath::arcTo (const Point& to) {
    
}

void PathRenderingPath::fill (PathRenderingPaint* paint) {
    
}

void PathRenderingPath::stroke (PathRenderingPaint* paint) {
    
}

void PathRenderingPath::line (const Point& from, const Point& to) {
    
}

void PathRenderingPath::polygon (const std::vector<Point>& points) {
    
}

void PathRenderingPath::rect (const Point& origin, const Size& size) {
    
}

void PathRenderingPath::roundRect (const Point& origin, const Size& size, const Size& arcSize) {
    
}

void PathRenderingPath::ellipse (const Point& center, const Size& size) {
    
}

void PathRenderingPath::arc (const Point& center, const Size& size, float startAngle, float angleExtent, PathRenderingPath::ArcType arcType) {
    
}

void PathRenderingPath::triangle (const Point &p1, const Point &p2, const Point &p3) {
    
}

void PathRenderingPath::quadraticBezierCurve(const Point& from, const Point& control, const Point& to, unsigned int segments) {
    
}

void PathRenderingPath::cubicBezierCurve(const Point& from, const Point& control1, const Point& control2, const Point& to, unsigned int segments) {
    
}


#pragma mark - tesseleator callbacks

void PathRenderingPath::tessBegin( GLenum type, GLvoid* user ) {
    
}

void PathRenderingPath::tessEnd( GLvoid* user ) {
    
}

void PathRenderingPath::tessVertex( GLvoid *vertex, GLvoid* user ) {
    
}

void PathRenderingPath::tessCombine( GLdouble coords[3], void *data[4],
                                    GLfloat weight[4], void **outData,
                                    void *polygonData ) {
    
}

void PathRenderingPath::tessError( GLenum errorCode ) {
    
}

void PathRenderingPath::endOfTesselation( unsigned int paintModes ) {
    
}


#pragma mark - utility methods

void PathRenderingPath::buildFill() {
    
}

void PathRenderingPath::buildStroke() {
    
}

void PathRenderingPath::buildFatLineSegment( std::vector<v2_t>& vertices, const v2_t& p0, const v2_t& p1, const float radius ) {
    
}

int32_t PathRenderingPath::segmentToNumCoordinates(PathSegment segment)
{
    static const int32_t coords[13] = {0,2,2,1,1,4,6,2,4,5,5,5,5};
    return coords[(int32_t)segment >> 1];
}

void PathRenderingPath::appendData( const int numSegments, const unsigned char* pathSegments, const void* pathData )
{
    int numCoords = 0;
    for( int i = 0; i < numSegments; i++ ) {
        _segments.push_back(pathSegments[i] );
        numCoords += segmentToNumCoordinates( static_cast<PathSegment>( pathSegments[i] ) );
    }
    
    _numSegments += numSegments;
    _numCoords += numCoords;
    
    for( int i = 0; i < numCoords; i++ ) {
        _fcoords.push_back( *(((float*)(pathData)) + i) );
    }
    
    this->setIsDirty( true );
}

NS_CC_EXT_END
