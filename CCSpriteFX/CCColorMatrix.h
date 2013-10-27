//
//  CCColorMatrix.h
//  CCSpriteFX
//
//  Created by bman on 7/23/13.
//
//

#ifndef __CCColorMatrix__
#define __CCColorMatrix__

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN


// color component luminance
#define kCCColorMatrixRLUM          (0.3086f)
#define kCCColorMatrixGLUM          (0.6094f)
#define kCCColorMatrixBLUM          (0.0820f)

// 4x4, column-major order, RGB + offset color matrix
typedef union _ColorMatrix4x4 {
    struct {
        GLfloat c0r0, c0r1, c0r2, c0r3;
        GLfloat c1r0, c1r1, c1r2, c1r3;
        GLfloat c2r0, c2r1, c2r2, c2r3;
        GLfloat c3r0, c3r1, c3r2, c3r3;
    };
    GLfloat m[16];
} ColorMatrix4x4;

CC_DLL ColorMatrix4x4 CCColorMatrixMakeIdentity ();
CC_DLL ColorMatrix4x4 CCColorMatrixMakeInversion (); // color inversion
CC_DLL ColorMatrix4x4 CCColorMatrixMakeScale (float rn, float gn, float bn); // param is 0~1
CC_DLL ColorMatrix4x4 CCColorMatrixMakeOffset (float rn, float gn, float bn); // param is -1~1
CC_DLL ColorMatrix4x4 CCColorMatrixMakeBrightness (float n); // param is -1~1
CC_DLL ColorMatrix4x4 CCColorMatrixMakeSaturation (float n); // param is 0~1
CC_DLL ColorMatrix4x4 CCColorMatrixMakeContrast (float n); // param is 0~1
CC_DLL ColorMatrix4x4 CCColorMatrixMakeThreshold (float n); // param is -1~1
CC_DLL ColorMatrix4x4 CCColorMatrixMakeHUE (float n); // param is -1~1
CC_DLL ColorMatrix4x4 CCColorMatrixConcat (const ColorMatrix4x4* M1, const ColorMatrix4x4* M2);
CC_DLL void printCCColorMatrix (const ColorMatrix4x4* M);


NS_CC_EXT_END

#endif /* defined(__CCColorMatrix__) */
