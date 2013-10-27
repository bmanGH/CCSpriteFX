//
//  CCColorMatrix.cpp
//  CCSpriteFX
//
//  Created by bman on 7/23/13.
//
//

#include "CCColorMatrix.h"
#include "math.h"

NS_CC_EXT_BEGIN


ColorMatrix4x4 CCColorMatrixMakeIdentity () {
    ColorMatrix4x4 cmat4;
    cmat4.m[0] = 1;  cmat4.m[1] = 0;  cmat4.m[2] = 0;  cmat4.m[3] = 0;
    cmat4.m[4] = 0;  cmat4.m[5] = 1;  cmat4.m[6] = 0;  cmat4.m[7] = 0;
    cmat4.m[8] = 0;  cmat4.m[9] = 0;  cmat4.m[10] = 1; cmat4.m[11] = 0;
    cmat4.m[12] = 0; cmat4.m[13] = 0; cmat4.m[14] = 0; cmat4.m[15] = 1;
    return cmat4;
}

CC_DLL ColorMatrix4x4 CCColorMatrixMakeInversion () {
    ColorMatrix4x4 cmat4;
    cmat4.m[0] = -1;  cmat4.m[1] = 0;  cmat4.m[2] = 0;  cmat4.m[3] = 0;
    cmat4.m[4] = 0;  cmat4.m[5] = -1;  cmat4.m[6] = 0;  cmat4.m[7] = 0;
    cmat4.m[8] = 0;  cmat4.m[9] = 0;  cmat4.m[10] = -1; cmat4.m[11] = 0;
    cmat4.m[12] = 1; cmat4.m[13] = 1; cmat4.m[14] = 1; cmat4.m[15] = 0;
    return cmat4;
}

CC_DLL ColorMatrix4x4 CCColorMatrixMakeScale (float rn, float gn, float bn) {
    ColorMatrix4x4 cmat4;
    cmat4.m[0] = rn;  cmat4.m[1] = 0;  cmat4.m[2] = 0;  cmat4.m[3] = 0;
    cmat4.m[4] = 0;  cmat4.m[5] = gn;  cmat4.m[6] = 0;  cmat4.m[7] = 0;
    cmat4.m[8] = 0;  cmat4.m[9] = 0;  cmat4.m[10] = bn; cmat4.m[11] = 0;
    cmat4.m[12] = 0; cmat4.m[13] = 0; cmat4.m[14] = 0; cmat4.m[15] = 1;
    return cmat4;
}

CC_DLL ColorMatrix4x4 CCColorMatrixMakeOffset (float rn, float gn, float bn) {
    ColorMatrix4x4 cmat4;
    cmat4.m[0] = 1;  cmat4.m[1] = 0;  cmat4.m[2] = 0;  cmat4.m[3] = 0;
    cmat4.m[4] = 0;  cmat4.m[5] = 1;  cmat4.m[6] = 0;  cmat4.m[7] = 0;
    cmat4.m[8] = 0;  cmat4.m[9] = 0;  cmat4.m[10] = 1; cmat4.m[11] = 0;
    cmat4.m[12] = rn; cmat4.m[13] = gn; cmat4.m[14] = bn; cmat4.m[15] = 1;
    return cmat4;
}

CC_DLL ColorMatrix4x4 CCColorMatrixMakeBrightness (float n) {
    ColorMatrix4x4 cmat4;
    cmat4.m[0] = 1;  cmat4.m[1] = 0;  cmat4.m[2] = 0;  cmat4.m[3] = 0;
    cmat4.m[4] = 0;  cmat4.m[5] = 1;  cmat4.m[6] = 0;  cmat4.m[7] = 0;
    cmat4.m[8] = 0;  cmat4.m[9] = 0;  cmat4.m[10] = 1; cmat4.m[11] = 0;
    cmat4.m[12] = n; cmat4.m[13] = n; cmat4.m[14] = n; cmat4.m[15] = 1;
    return cmat4;
}

CC_DLL ColorMatrix4x4 CCColorMatrixMakeSaturation (float n) {
    ColorMatrix4x4 cmat4;
    cmat4.m[0] = kCCColorMatrixRLUM * (1-n) + n;  cmat4.m[1] = kCCColorMatrixRLUM * (1-n);  cmat4.m[2] = kCCColorMatrixRLUM * (1-n);  cmat4.m[3] = 0;
    cmat4.m[4] = kCCColorMatrixGLUM * (1-n);  cmat4.m[5] = kCCColorMatrixGLUM * (1-n) + n;  cmat4.m[6] = kCCColorMatrixGLUM * (1-n);  cmat4.m[7] = 0;
    cmat4.m[8] = kCCColorMatrixBLUM * (1-n);  cmat4.m[9] = kCCColorMatrixBLUM * (1-n);  cmat4.m[10] = kCCColorMatrixBLUM * (1-n) + n; cmat4.m[11] = 0;
    cmat4.m[12] = 0; cmat4.m[13] = 0; cmat4.m[14] = 0; cmat4.m[15] = 1;
    return cmat4;
}

CC_DLL ColorMatrix4x4 CCColorMatrixMakeContrast (float n) {
    ColorMatrix4x4 cmat4;
    cmat4.m[0] = n;  cmat4.m[1] = 0;  cmat4.m[2] = 0;  cmat4.m[3] = 0;
    cmat4.m[4] = 0;  cmat4.m[5] = n;  cmat4.m[6] = 0;  cmat4.m[7] = 0;
    cmat4.m[8] = 0;  cmat4.m[9] = 0;  cmat4.m[10] = n; cmat4.m[11] = 0;
    cmat4.m[12] = 0.5f * (1 - n); cmat4.m[13] = 0.5f * (1 - n); cmat4.m[14] = 0.5f * (1 - n); cmat4.m[15] = 1;
    return cmat4;
}

CC_DLL ColorMatrix4x4 CCColorMatrixMakeThreshold (float n) {
    ColorMatrix4x4 cmat4;
    cmat4.m[0] = kCCColorMatrixRLUM * 256.0f;  cmat4.m[1] = kCCColorMatrixRLUM * 256.0f;  cmat4.m[2] = kCCColorMatrixRLUM * 256.0f;  cmat4.m[3] = 0;
    cmat4.m[4] = kCCColorMatrixGLUM * 256.0f;  cmat4.m[5] = kCCColorMatrixGLUM * 256.0f;  cmat4.m[6] = kCCColorMatrixGLUM * 256.0f;  cmat4.m[7] = 0;
    cmat4.m[8] = kCCColorMatrixBLUM * 256.0f;  cmat4.m[9] = kCCColorMatrixBLUM * 256.0f;  cmat4.m[10] = kCCColorMatrixBLUM * 256.0f; cmat4.m[11] = 0;
    cmat4.m[12] = -128.0f + -128.0f * n; cmat4.m[13] = -128.0f + -128.0f * n; cmat4.m[14] = -128.0f + -128.0f * n; cmat4.m[15] = 1;
    return cmat4;
}

CC_DLL ColorMatrix4x4 CCColorMatrixMakeHUE (float n) {
    ColorMatrix4x4 cmat4;
    
    n *= M_PI;
    float cos = cosf(n);
    float sin = sinf(n);
    
    cmat4.m[0] = ((kCCColorMatrixRLUM + (cos * (1 - kCCColorMatrixRLUM))) + (sin * -(kCCColorMatrixRLUM)));
    cmat4.m[4] = ((kCCColorMatrixGLUM + (cos * -(kCCColorMatrixGLUM))) + (sin * -(kCCColorMatrixGLUM)));
    cmat4.m[8] = ((kCCColorMatrixBLUM + (cos * -(kCCColorMatrixBLUM))) + (sin * (1 - kCCColorMatrixBLUM)));
    cmat4.m[12] = 0;
    
    cmat4.m[1] = ((kCCColorMatrixRLUM + (cos * -(kCCColorMatrixRLUM))) + (sin * 0.143f));
    cmat4.m[5] = ((kCCColorMatrixGLUM + (cos * (1 - kCCColorMatrixGLUM))) + (sin * 0.14f));
    cmat4.m[9] = ((kCCColorMatrixBLUM + (cos * - (kCCColorMatrixBLUM))) + (sin * -0.283f));
    cmat4.m[13] = 0;
    
    cmat4.m[2] = ((kCCColorMatrixRLUM + (cos * -(kCCColorMatrixRLUM))) + (sin * -((1 - kCCColorMatrixRLUM))));
    cmat4.m[6] = ((kCCColorMatrixGLUM + (cos * -(kCCColorMatrixGLUM))) + (sin * kCCColorMatrixGLUM));
    cmat4.m[10] = ((kCCColorMatrixBLUM + (cos * (1 - kCCColorMatrixBLUM))) + (sin * kCCColorMatrixBLUM));
    cmat4.m[14] = 0;
    
    cmat4.m[3] = 0;
    cmat4.m[7] = 0;
    cmat4.m[11] = 0;
    cmat4.m[15] = 1;
    
    return cmat4;
}

ColorMatrix4x4 CCColorMatrixConcat (const ColorMatrix4x4* M1, const ColorMatrix4x4* M2) {
    ColorMatrix4x4 ret;
    const GLfloat *m1 = M1->m, *m2 = M2->m;
    GLfloat *mat = ret.m;
    
    mat[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
    mat[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
    mat[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
    mat[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];
    
    mat[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
    mat[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
    mat[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
    mat[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];
    
    mat[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
    mat[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
    mat[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
    mat[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];
    
    mat[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
    mat[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
    mat[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
    mat[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];
    
    return ret;
}

void printCCColorMatrix (ColorMatrix4x4* M) {
    CCLOG("[");
    for(int r = 0; r < 4; r++) {
        CCLOG("\t%f, %f, %f, %f", M->m[4 * r + 0], M->m[4 * r + 1], M->m[4 * r + 2], M->m[4 * r + 3]);
    }
    CCLOG("]");
}


NS_CC_EXT_END
