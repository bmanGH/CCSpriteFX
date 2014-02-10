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


static inline float radians (float degrees) { return (float)(degrees * (M_PI/180.0f)); }
static inline float degrees (float radians) { return (float)(radians * (180.0f/M_PI)); }

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


PathRenderingPath::PathRenderingPath(int segmentCapacityHint,
                                     int coordCapacityHint,
                                     int tessellationIterations,
                                     GLenum bufferMode)
: _numSegments(segmentCapacityHint),
_numCoords(coordCapacityHint),
_fcoords(coordCapacityHint),
_tessellationIterations(tessellationIterations),
_isFillDirty(true),
_isStrokeDirty(true),
_minX(MAXFLOAT),
_minY(MAXFLOAT),
_height(-MAXFLOAT),
_width(-MAXFLOAT),
_fillTesseleator(0),
_primType(0),
_bufferMode(bufferMode),
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
    
    _fillTesseleator = 0;
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

void PathRenderingPath::fill (PathRenderingPaint* paint, PathFillRule fillRule) {
    _vertices.clear();
    
    // reset the bounds
    _minX = MAXFLOAT;
    _minY = MAXFLOAT;
    _width = -MAXFLOAT;
    _height = -MAXFLOAT;
    
    CHECK_GL_ERROR_DEBUG();
    
#ifndef APIENTRY
    #define APIENTRY
#endif // APIENTRY
    
    _fillTesseleator = gluNewTess();
    gluTessCallback( _fillTesseleator, GLU_TESS_BEGIN_DATA, (GLvoid (APIENTRY *) ( )) &PathRenderingPath::tessBegin );
    gluTessCallback( _fillTesseleator, GLU_TESS_END_DATA, (GLvoid (APIENTRY *) ( )) &PathRenderingPath::tessEnd );
    gluTessCallback( _fillTesseleator, GLU_TESS_VERTEX_DATA, (GLvoid (APIENTRY *) ( )) &PathRenderingPath::tessVertex );
    gluTessCallback( _fillTesseleator, GLU_TESS_COMBINE_DATA, (GLvoid (APIENTRY *) ( )) &PathRenderingPath::tessCombine );
    gluTessCallback( _fillTesseleator, GLU_TESS_ERROR, (GLvoid (APIENTRY *)())&PathRenderingPath::tessError );
    if( fillRule == FILL_RULE_EVEN_ODD ) {
        gluTessProperty( _fillTesseleator, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ODD );
    } else if( fillRule == FILL_RULE_NON_ZERO ) {
        gluTessProperty( _fillTesseleator, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_NONZERO );
    }
    gluTessProperty( _fillTesseleator, GLU_TESS_TOLERANCE, 0.5f );
    
    gluTessBeginPolygon( _fillTesseleator, this );
    
    std::vector< float >::iterator coordsIter = _fcoords.begin();
    int numCoords = 0;
    unsigned int segment = PATH_CLOSE_PATH;
    v2_t coords = {0,0};
    v2_t prev = {0,0};
    v2_t closeTo = {0,0};
    int num_contours = 0;
    
    for ( std::vector< unsigned int >::iterator segmentIter = _segments.begin(); segmentIter != _segments.end(); segmentIter++ ) {
        segment = (*segmentIter);
        numCoords = this->segmentToNumCoordinates( static_cast<PathSegment>( segment ) );
        //segment = segment >> 1;
        
        //			PATH_CLOSE_PATH                               = ( 0 << 1),
        //			PATH_MOVE_TO                                  = ( 1 << 1),
        //			PATH_LINE_TO                                  = ( 2 << 1),
        //			PATH_HLINE_TO                                 = ( 3 << 1),
        //			PATH_VLINE_TO                                 = ( 4 << 1),
        //			PATH_QUAD_TO                                  = ( 5 << 1),
        //			PATH_CUBIC_TO                                 = ( 6 << 1),
        //			PATH_SQUAD_TO                                 = ( 7 << 1),
        //			PATH_SCUBIC_TO                                = ( 8 << 1),
        //			PATH_SCCWARC_TO                               = ( 9 << 1),
        //			PATH_SCWARC_TO                                = (10 << 1),
        //			PATH_LCCWARC_TO                               = (11 << 1),
        //			PATH_LCWARC_TO                                = (12 << 1),
        
        switch (segment >> 1) {
            case (PATH_CLOSE_PATH >> 1):
            {
                //GLdouble* c = new GLdouble[3];
                v3_t c(closeTo);
                _tessVertices.push_back( c );
                //					c[0] = closeTo.x;
                //					c[1] = closeTo.y;
                //					c[2] = 0;
                // do not think this is necessary for the tesselator
                gluTessVertex( _fillTesseleator, tessVerticesBackPtr(), tessVerticesBackPtr() );
                
                if ( num_contours ) {
                    gluTessEndContour( _fillTesseleator );
                    num_contours--;
                }
            } break;
            case (PATH_MOVE_TO >> 1):
            {
                if ( num_contours ) {
                    gluTessEndContour( _fillTesseleator );
                    num_contours--;
                }
                
                gluTessBeginContour( _fillTesseleator );
                num_contours++;
                closeTo.x = coords.x = *coordsIter; coordsIter++;
                closeTo.y = coords.y = *coordsIter; coordsIter++;
                
                v3_t c( coords );
                _tessVertices.push_back( c );
                gluTessVertex( _fillTesseleator, tessVerticesBackPtr(), tessVerticesBackPtr() );
                
            } break;
            case (PATH_LINE_TO >> 1):
            {
                prev = coords;
                coords.x = *coordsIter; coordsIter++;
                coords.y = *coordsIter; coordsIter++;
                
                v3_t c( coords );
                _tessVertices.push_back( c );
                gluTessVertex( _fillTesseleator, tessVerticesBackPtr(), tessVerticesBackPtr() );
            } break;
            case (PATH_HLINE_TO >> 1):
            {
                prev = coords;
                coords.x = *coordsIter; coordsIter++;
                
                v3_t c( coords );
                _tessVertices.push_back( c );
                gluTessVertex( _fillTesseleator, tessVerticesBackPtr(), tessVerticesBackPtr() );
            } break;
            case (PATH_VLINE_TO >> 1):
            {
                prev = coords;
                coords.y = *coordsIter; coordsIter++;
                
                v3_t c( coords );
                _tessVertices.push_back( c );
                gluTessVertex( _fillTesseleator, tessVerticesBackPtr(), tessVerticesBackPtr() );
            } break;
            case (PATH_SCUBIC_TO >> 1):
            {
                prev = coords;
                float cp2x = *coordsIter; coordsIter++;
                float cp2y = *coordsIter; coordsIter++;
                float p3x = *coordsIter; coordsIter++;
                float p3y = *coordsIter; coordsIter++;
                
                float cp1x = 2.0f * cp2x - p3x;
                float cp1y = 2.0f * cp2y - p3y;
                
                float increment = 1.0f / _tessellationIterations;
                //printf("\tcubic: ");
                for ( float t = increment; t < 1.0f + increment; t+=increment ) {
                    v3_t c;
                    c.x = calcCubicBezier1d( coords.x, cp1x, cp2x, p3x, t );
                    c.y = calcCubicBezier1d( coords.y, cp1y, cp2y, p3y, t );
                    _tessVertices.push_back( c );
                    gluTessVertex( _fillTesseleator, tessVerticesBackPtr(), tessVerticesBackPtr() );
                    //	c.print();
                }
                //printf("\n");
                coords.x = p3x;
                coords.y = p3y;
            } break;
            case (PATH_CUBIC_TO >> 1):
            {
                prev = coords;
                float cp1x = *coordsIter; coordsIter++;
                float cp1y = *coordsIter; coordsIter++;
                float cp2x = *coordsIter; coordsIter++;
                float cp2y = *coordsIter; coordsIter++;
                float p3x = *coordsIter; coordsIter++;
                float p3y = *coordsIter; coordsIter++;
                
                float increment = 1.0f / _tessellationIterations;
                //printf("\tcubic: ");
                for ( float t = increment; t < 1.0f + increment; t+=increment ) {
                    v3_t c;
                    c.x = calcCubicBezier1d( coords.x, cp1x, cp2x, p3x, t );
                    c.y = calcCubicBezier1d( coords.y, cp1y, cp2y, p3y, t );
                    _tessVertices.push_back( c );
                    gluTessVertex( _fillTesseleator, tessVerticesBackPtr(), tessVerticesBackPtr() );
					//	c.print();
                }
                //printf("\n");
                coords.x = p3x;
                coords.y = p3y;
            } break;
            case (PATH_QUAD_TO >> 1):
            {
                prev = coords;
                float cpx = *coordsIter; coordsIter++;
                float cpy = *coordsIter; coordsIter++;
                float px = *coordsIter; coordsIter++;
                float py = *coordsIter; coordsIter++;
                
                float increment = 1.0f / _tessellationIterations;
                for ( float t = increment; t < 1.0f + increment; t+=increment ) {
                    v3_t c;
                    c.x = calcQuadBezier1d( coords.x, cpx, px, t );
                    c.y = calcQuadBezier1d( coords.y, cpy, py, t );
                    _tessVertices.push_back( c );
                    gluTessVertex( _fillTesseleator, tessVerticesBackPtr(), tessVerticesBackPtr() );
                }
                
                coords.x = px;
                coords.y = py;
                
            } break;
            case (PATH_SCCWARC_TO >> 1):
            case (PATH_SCWARC_TO >> 1):
            case (PATH_LCCWARC_TO >> 1):
            case (PATH_LCWARC_TO >> 1):
            {
                float rh = *coordsIter; coordsIter++;
                float rv = *coordsIter; coordsIter++;
                float rot = *coordsIter; coordsIter++;
                float cp1x = *coordsIter; coordsIter++;
                float cp1y = *coordsIter; coordsIter++;
                
                // convert to Center Parameterization (see OpenVG Spec Apendix A)
                float cx0[2];
                float cx1[2];
                bool success = findEllipses( rh, rv, rot,
                                                 coords.x, coords.y, cp1x, cp1y,
                                                 &cx0[0], &cx0[1], &cx1[0], &cx1[1] );
                
                if ( success ) {
                    // see: http://en.wikipedia.org/wiki/Ellipse#Ellipses_in_computer_graphics
                    const int steps = _tessellationIterations;
                    float beta = 0;	// angle. todo
                    float sinbeta = sinf( beta );
                    float cosbeta = cosf( beta );
                    
                    // calculate the start and end angles
                    v2_t center;
                    center.x = cx0[0];
                    center.y = cx0[1];
                    v2_t norm[2];
                    norm[0].x = center.x - coords.x;
                    norm[0].y = center.y - coords.y;
                    float inverse_len = 1.0f/sqrtf( (norm[0].x * norm[0].x) + (norm[0].y * norm[0].y) );
                    norm[0].x *= inverse_len;
                    norm[0].y *= inverse_len;
                    
                    norm[1].x = center.x - cp1x;
                    norm[1].y = center.y - cp1y;
                    inverse_len = 1.0f/sqrtf( (norm[1].x * norm[1].x) + (norm[1].y * norm[1].y) );
                    norm[1].x *= inverse_len;
                    norm[1].y *= inverse_len;
                    float startAngle = degrees( acosf( -norm[0].x ) );
                    float endAngle = degrees( acosf( -norm[1].x ) );
                    
                    float cross = norm[0].x;
                    
                    if ( cross >= 0  ) {
                        startAngle = 360 - startAngle;
                        endAngle = 360 - endAngle;
                    }
                    if ( startAngle > endAngle ) {
                        float tmp = startAngle;
                        startAngle = endAngle;
                        endAngle = tmp;
                        startAngle = startAngle - 90;
                        endAngle = endAngle - 90;
                    }
                    for ( float g = startAngle; g < endAngle; g+=360/steps ) {
                        v3_t c;
                        
                        float alpha = g * (M_PI / 180.0f);
                        float sinalpha = sinf( alpha );
                        float cosalpha = cosf( alpha );
                        c.x = cx0[0] + (rh * cosalpha * cosbeta - rv * sinalpha * sinbeta);
                        c.y = cx0[1] + (rh * cosalpha * sinbeta + rv * sinalpha * cosbeta);
                        _tessVertices.push_back( c );
                        gluTessVertex( _fillTesseleator, tessVerticesBackPtr(), tessVerticesBackPtr() );
                    }
                }
                
                coords.x = cp1x;
                coords.y = cp1y;
                
            } break;
            default:
                printf("unkwown command\n");
                break;
        }
    }	// foreach segment
    
    if ( num_contours ) {
        gluTessEndContour( _fillTesseleator );
        num_contours--;
    }
    
    assert(num_contours == 0);
    
    gluTessEndPolygon( _fillTesseleator );
    
    gluDeleteTess( _fillTesseleator );
    
    _fillTesseleator = 0;
    
    CHECK_GL_ERROR_DEBUG();
}

void PathRenderingPath::stroke (PathRenderingPaint* paint, float lineWidth) {
    _strokeVertices.clear();
    
    const float stroke_width = lineWidth;
    
    std::vector< float >::iterator coordsIter = _fcoords.begin();
    int numCoords = 0;
    unsigned int segment = PATH_CLOSE_PATH;
    v2_t coords = {0,0};
    v2_t prev = {0,0};
    v2_t closeTo = {0,0};
    //vector<v2_t> vertices;
    for ( std::vector< unsigned int >::iterator segmentIter = _segments.begin(); segmentIter != _segments.end(); segmentIter++ ) {
        segment = (*segmentIter);
        numCoords = this->segmentToNumCoordinates( static_cast<PathSegment>( segment ) );
        //segment = segment >> 1;
        
        //			PATH_CLOSE_PATH                               = ( 0 << 1),
        //			PATH_MOVE_TO                                  = ( 1 << 1),
        //			PATH_LINE_TO                                  = ( 2 << 1),
        //			PATH_HLINE_TO                                 = ( 3 << 1),
        //			PATH_VLINE_TO                                 = ( 4 << 1),
        //			PATH_QUAD_TO                                  = ( 5 << 1),
        //			PATH_CUBIC_TO                                 = ( 6 << 1),
        //			PATH_SQUAD_TO                                 = ( 7 << 1),
        //			PATH_SCUBIC_TO                                = ( 8 << 1),
        //			PATH_SCCWARC_TO                               = ( 9 << 1),
        //			PATH_SCWARC_TO                                = (10 << 1),
        //			PATH_LCCWARC_TO                               = (11 << 1),
        //			PATH_LCWARC_TO                                = (12 << 1),
        
        switch (segment >> 1) {
            case (PATH_CLOSE_PATH >> 1):
            {
                buildFatLineSegment( _strokeVertices, coords, closeTo, stroke_width );
            } break;
            case (PATH_MOVE_TO >> 1):
            {
                prev.x = closeTo.x = coords.x = *coordsIter; coordsIter++;
                prev.y = closeTo.y = coords.y = *coordsIter; coordsIter++;
            } break;
            case (PATH_LINE_TO >> 1):
            {
                prev = coords;
                coords.x = *coordsIter; coordsIter++;
                coords.y = *coordsIter; coordsIter++;
                
                buildFatLineSegment( _strokeVertices, prev, coords, stroke_width );
            } break;
            case (PATH_HLINE_TO >> 1):
            {
                prev = coords;
                coords.x = *coordsIter; coordsIter++;
                
                buildFatLineSegment( _strokeVertices, prev, coords, stroke_width );
            } break;
            case (PATH_VLINE_TO >> 1):
            {
                prev = coords;
                coords.y = *coordsIter; coordsIter++;
                
                buildFatLineSegment( _strokeVertices, prev, coords, stroke_width );
            } break;
            case (PATH_SCUBIC_TO >> 1):
            {
                prev = coords;
                float cp2x = *coordsIter; coordsIter++;
                float cp2y = *coordsIter; coordsIter++;
                float p3x = *coordsIter; coordsIter++;
                float p3y = *coordsIter; coordsIter++;
                
                float cp1x = 2.0f * cp2x - p3x;
                float cp1y = 2.0f * cp2y - p3y;
                
                float increment = 1.0f / _tessellationIterations;
                //printf("\tcubic: ");
                for ( float t = increment; t < 1.0f + increment; t+=increment ) {
                    v2_t c;
                    c.x = calcCubicBezier1d( coords.x, cp1x, cp2x, p3x, t );
                    c.y = calcCubicBezier1d( coords.y, cp1y, cp2y, p3y, t );
                    buildFatLineSegment( _strokeVertices, prev, c, stroke_width );
                    prev = c;
                }
                coords.x = p3x;
                coords.y = p3y;
                
            } break;
            case (PATH_CUBIC_TO >> 1):	// todo
            {
                prev = coords;
                float cp1x = *coordsIter; coordsIter++;
                float cp1y = *coordsIter; coordsIter++;
                float cp2x = *coordsIter; coordsIter++;
                float cp2y = *coordsIter; coordsIter++;
                float p3x = *coordsIter; coordsIter++;
                float p3y = *coordsIter; coordsIter++;
                
                float increment = 1.0f / _tessellationIterations;
                
                for ( float t = increment; t < 1.0f + increment; t+=increment ) {
                    v2_t c;
                    c.x = calcCubicBezier1d( coords.x, cp1x, cp2x, p3x, t );
                    c.y = calcCubicBezier1d( coords.y, cp1y, cp2y, p3y, t );
                    buildFatLineSegment( _strokeVertices, prev, c, stroke_width );
                    prev = c;
                }
                coords.x = p3x;
                coords.y = p3y;
                
            } break;
            case (PATH_SCCWARC_TO >> 1):
            case (PATH_SCWARC_TO >> 1):
            case (PATH_LCCWARC_TO >> 1):
            case (PATH_LCWARC_TO >> 1):
            {
                float rh = *coordsIter; coordsIter++;
                float rv = *coordsIter; coordsIter++;
                float rot = *coordsIter; coordsIter++;
                float cp1x = *coordsIter; coordsIter++;
                float cp1y = *coordsIter; coordsIter++;
                
                // convert to Center Parameterization (see OpenVG Spec Apendix A)
                float cx0[2];
                float cx1[2];
                bool success = findEllipses( rh, rv, rot,
                                                 coords.x, coords.y, cp1x, cp1y,
                                                 &cx0[0], &cx0[1], &cx1[0], &cx1[1] );
                
                if ( success ) {
                    // see: http://en.wikipedia.org/wiki/Ellipse#Ellipses_in_computer_graphics
                    const int steps = _tessellationIterations;
                    float beta = 0;	// angle. todo
                    float sinbeta = sinf( beta );
                    float cosbeta = cosf( beta );
                    
                    // calculate the start and end angles
                    v2_t center;
                    center.x = cx0[0];//(cx0[0] + cx1[0])*0.5f;
                    center.y = cx0[1];//(cx0[1] + cx1[1])*0.5f;
                    v2_t norm[2];
                    norm[0].x = center.x - coords.x;
                    norm[0].y = center.y - coords.y;
                    float inverse_len = 1.0f/sqrtf( (norm[0].x * norm[0].x) + (norm[0].y * norm[0].y) );
                    norm[0].x *= inverse_len;
                    norm[0].y *= inverse_len;
                    
                    norm[1].x = center.x - cp1x;
                    norm[1].y = center.y - cp1y;
                    inverse_len = 1.0f/sqrtf( (norm[1].x * norm[1].x) + (norm[1].y * norm[1].y) );
                    norm[1].x *= inverse_len;
                    norm[1].y *= inverse_len;
                    float startAngle = degrees( acosf( -norm[0].x ) );
                    float endAngle = degrees( acosf( -norm[1].x ) );
                    float cross = norm[0].x;
                    if ( cross >= 0 ) {
                        startAngle = 360 - startAngle;
                        endAngle = 360 - endAngle;
                    }
                    if ( startAngle > endAngle ) {
                        float tmp = startAngle;
                        startAngle = endAngle;
                        endAngle = tmp;
                        startAngle = startAngle - 90;
                        endAngle = endAngle - 90;
                    }
                    
                    prev = coords;
                    for ( float g = startAngle; g < endAngle + (360/steps); g+=360/steps ) {
                        v2_t c;
                        
                        float alpha = g * (M_PI / 180.0f);
                        float sinalpha = sinf( alpha );
                        float cosalpha = cosf( alpha );
                        c.x = cx0[0] + (rh * cosalpha * cosbeta - rv * sinalpha * sinbeta);
                        c.y = cx0[1] + (rh * cosalpha * sinbeta + rv * sinalpha * cosbeta);
                        //printf( "(%f, %f)\n", c[0], c[1] );
                        buildFatLineSegment( _strokeVertices, prev, c, stroke_width );
                        prev = c;
                    }
                }
                
                coords.x = cp1x;
                coords.y = cp1y;
            } break;
            default:
                printf("unkwown command\n");
                break;
        }
    }	// foreach segment
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

GLvoid PathRenderingPath::tessBegin( GLenum type, GLvoid* user ) {
    PathRenderingPath* me = (PathRenderingPath*)user;
    me->setPrimType( type );
    me->vertexCount_ = 0;
    
    switch( type )
    {
        case GL_TRIANGLES:
            //printf( "begin(GL_TRIANGLES)\n" );
            break;
        case GL_TRIANGLE_FAN:
            //printf( "begin(GL_TRIANGLE_FAN)\n" );
            break;
        case GL_TRIANGLE_STRIP:
            //printf( "begin(GL_TRIANGLE_STRIP)\n" );
            break;
        case GL_LINE_LOOP:
            //printf( "begin(GL_LINE_LOOP)\n" );
            break;
        default:
            break;
    }
}

GLvoid PathRenderingPath::tessEnd( GLvoid* user ) {
    //PathRenderingPath* me = (PathRenderingPath*)user;
    //me->endOfTesselation();
    
    //printf("end\n");
}

GLvoid PathRenderingPath::tessVertex( GLvoid *vertex, GLvoid* user ) {
    PathRenderingPath* me = (PathRenderingPath*)user;
    GLdouble* v = (GLdouble*)vertex;
    
    if ( me->getPrimType() == GL_TRIANGLE_FAN ) {
        // break up fans and strips into triangles
        switch ( me->vertexCount_ ) {
            case 0:
                me->startVertex_[0] = v[0];
                me->startVertex_[1] = v[1];
                break;
            case 1:
                me->lastVertex_[0] = v[0];
                me->lastVertex_[1] = v[1];
                break;
                
            default:
                me->addVertex( me->startVertex_ );
                me->addVertex( me->lastVertex_ );
                me->addVertex( v );
                me->lastVertex_[0] = v[0];
                me->lastVertex_[1] = v[1];
                break;
        }
    } else if ( me->getPrimType() == GL_TRIANGLES ) {
        me->addVertex( v );
    } else if ( me->getPrimType() == GL_TRIANGLE_STRIP ) {
        switch ( me->vertexCount_ ) {
            case 0:
                me->addVertex( v );
                break;
            case 1:
                me->startVertex_[0] = v[0];
                me->startVertex_[1] = v[1];
                me->addVertex( v );
                break;
            case 2:
                me->lastVertex_[0] = v[0];
                me->lastVertex_[1] = v[1];
                me->addVertex( v );
                break;
                
            default:
                me->addVertex( me->startVertex_ );
                me->addVertex( me->lastVertex_ );
                me->addVertex( v );
                me->startVertex_[0] = me->lastVertex_[0];
                me->startVertex_[1] = me->lastVertex_[1];
                me->lastVertex_[0] = v[0];
                me->lastVertex_[1] = v[1];
                break;
        }
    }
    me->vertexCount_++;
    
    //printf("\tvert[%d]: %f, %f, %f\n", vertexCount_, v[0], v[1], v[2] );
}

GLvoid PathRenderingPath::tessCombine( GLdouble coords[3], void *data[4],
                                    GLfloat weight[4], void **outData,
                                    void *polygonData ) {
    PathRenderingPath* me = (PathRenderingPath*)polygonData;
    v3_t v;
    v.x = coords[0];
    v.y = coords[1];
    v.z = coords[2];
    me->addTessVertex( v );
    *outData = me->tessVerticesBackPtr();
}

GLvoid PathRenderingPath::tessError( GLenum errorCode ) {
    printf("tesselator error: [%d] %s\n", errorCode, gluErrorString( errorCode) );
}


#pragma mark - internal methods

void PathRenderingPath::endOfTesselation( unsigned int paintModes ) {
    // final calculation of the width and height
    _width = fabsf(_width - _minX);
    _height = fabsf(_height - _minY);
    
    /// build fill vbo
    // TODO: BUGBUG: if in batch mode don't build the VBO!
    if ( _vertices.size() > 0 ) {
        if ( _fillVBO != -1 ) {
            glDeleteBuffers( 1, &_fillVBO );
            _fillVBO = -1;
        }
        
        glGenBuffers( 1, &_fillVBO );
        glBindBuffer( GL_ARRAY_BUFFER, _fillVBO );
        if ( _fillPaintForPath &&
            _fillPaintForPath->getPaintType() == PathRenderingPaint::PAINT_TYPE_COLOR ) {
            glBufferData( GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), &_vertices[0], _bufferMode );
        } else if ( _fillPaintForPath &&
                   (_fillPaintForPath->getPaintType() == PathRenderingPaint::PAINT_TYPE_LINEAR_GRADIENT ||
                    _fillPaintForPath->getPaintType() == PathRenderingPaint::PAINT_TYPE_RADIAL_GRADIENT ||
                    _fillPaintForPath->getPaintType() == PathRenderingPaint::PAINT_TYPE_RADIAL_2x3_GRADIENT ||
                    _fillPaintForPath->getPaintType() == PathRenderingPaint::PAINT_TYPE_LINEAR_2x3_GRADIENT) ) {
                       std::vector<textured_vertex_t> texturedVertices;
                       for ( std::vector<float>::const_iterator it = _vertices.begin(); it != _vertices.end(); it++ ) {
                           // build up the textured vertex
                           textured_vertex_t v;
                           v.v[0] = *it;
                           it++;
                           v.v[1] = *it;
                           v.uv[0] = fabsf(v.v[0] - _minX) / _width;
                           v.uv[1] = fabsf( v.v[1] - _minY ) / _height;
                           texturedVertices.push_back( v );
                       }
                       
                       glBufferData( GL_ARRAY_BUFFER, texturedVertices.size() * sizeof(textured_vertex_t), &texturedVertices[0], _bufferMode );
                       
                       texturedVertices.clear();
                       
                       // setup the paints linear gradient
                       _fillPaintForPath->buildGradientImage( _width, _height );
                   }
        
        _numberFillVertices = (int)_vertices.size()/2;
        _tessVertices.clear();
    }
    
    /// build stroke vbo
    if ( _strokeVertices.size() > 0 ) {
        // build the vertex buffer object VBO
        if ( _strokeVBO != -1 ) {
            glDeleteBuffers( 1, &_strokeVBO );
            _strokeVBO = -1;
        }
        
        glGenBuffers( 1, &_strokeVBO );
        glBindBuffer( GL_ARRAY_BUFFER, _strokeVBO );
        glBufferData( GL_ARRAY_BUFFER, _strokeVertices.size() * sizeof(float) * 2, &_strokeVertices[0], _bufferMode );
        _numberStrokeVertices = (int)_strokeVertices.size();
    }
    
    // clear out vertex buffer
    _vertices.clear();
    _strokeVertices.clear();
}

void PathRenderingPath::buildFatLineSegment( std::vector<v2_t>& vertices, const v2_t& p0, const v2_t& p1, const float radius ) {
    if ( (p0.x == p1.x) && (p0.y == p1.y ) ) {
        return;
    }
    
    float dx = p1.y - p0.y;
    float dy = p0.x - p1.x;
    const float inv_mag = 1.0f / sqrtf(dx*dx + dy*dy);
    dx = dx * inv_mag;
    dy = dy * inv_mag;
    
    v2_t v0, v1, v2, v3;
    
    v0.x = p0.x + radius * dx;
    v0.y = p0.y + radius * dy;
    vertices.push_back( v0 );
    
    v1.x = p0.x - radius * dx;
    v1.y = p0.y - radius * dy;
    vertices.push_back( v1 );
    
    
    v2.x = p1.x + radius * dx;
    v2.y = p1.y + radius * dy;
    vertices.push_back( v2 );
    
    v3.x = p1.x - radius * dx;
    v3.y = p1.y - radius * dy;
    vertices.push_back( v3 );
    
//		printf("start stroke\n");
//		printf("p0: ");p0.print();
//		printf("p1: ");p1.print();
//		printf("\t"); v0.print();
//		printf("\t"); v1.print();
//		printf("\t"); v2.print();
//		printf("\t"); v3.print();
//		printf("end stroke\n");
}

int32_t PathRenderingPath::segmentToNumCoordinates(PathSegment segment)
{
    static const int32_t coords[13] = {0,2,2,1,1,4,6,2,4,5,5,5,5};
    return coords[(int32_t)segment >> 1];
}

void PathRenderingPath::appendData( const int numSegments, const unsigned int* pathSegments, const void* pathData )
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
