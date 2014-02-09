#include "CCColorMatrixFunctionalTestScene.h"


Scene* CCColorMatrixFunctionalTestScene::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    CCColorMatrixFunctionalTestScene *layer = CCColorMatrixFunctionalTestScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

CCColorMatrixFunctionalTestScene::~CCColorMatrixFunctionalTestScene () {
    
}

bool CCColorMatrixFunctionalTestScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    spr1 = SpriteFX::create("image/icon.png");
    spr1->setPosition(Point(winSize.width / 4, winSize.height / 4));
    this->addChild(spr1);
    
    spr2 = SpriteFX::create("image/icon.png");
    spr2->setPosition(Point(winSize.width / 4 * 2, winSize.height / 4));
    this->addChild(spr2);
    
    spr3 = SpriteFX::create("image/icon.png");
    spr3->setPosition(Point(winSize.width / 4 * 3, winSize.height / 4));
    this->addChild(spr3);
    
    spr4 = SpriteFX::create("image/icon.png");
    spr4->setPosition(Point(winSize.width / 4, winSize.height / 4 * 2));
    this->addChild(spr4);
    
    spr5 = SpriteFX::create("image/icon.png");
    spr5->setPosition(Point(winSize.width / 4 * 2, winSize.height / 4 * 2));
    this->addChild(spr5);
    
    spr6 = SpriteFX::create("image/icon.png");
    spr6->setPosition(Point(winSize.width / 4 * 3, winSize.height / 4 * 2));
    this->addChild(spr6);
    
    spr7 = SpriteFX::create("image/icon.png");
    spr7->setPosition(Point(winSize.width / 4, winSize.height / 4 * 3));
    this->addChild(spr7);
    
    spr8 = SpriteFX::create("image/icon.png");
    spr8->setPosition(Point(winSize.width / 4 * 2, winSize.height / 4 * 3));
    this->addChild(spr8);
    
    spr9 = SpriteFX::create("image/icon.png");
    spr9->setPosition(Point(winSize.width / 4 * 3, winSize.height / 4 * 3));
    this->addChild(spr9);
    
    // ColorMatrix test
//    this->scheduleUpdate();
    
    // ColorMatrix Actions test
    spr1->runAction(RepeatForever::create(Sequence::create(ColorMatrixScale::create(0.5, 0, 1, 0, 0, 0, 0), ColorMatrixScale::create(0.5, 1, 0, 0, 0, 0, 0), ColorMatrixScale::create(0.5, 0, 0, 0, 1, 0, 0), ColorMatrixScale::create(0.5, 0, 0, 1, 0, 0, 0), ColorMatrixScale::create(0.5, 0, 0, 0, 0, 0, 1), ColorMatrixScale::create(0.5, 0, 0, 0, 0, 1, 0), nullptr)));
    
    spr2->runAction(RepeatForever::create(Sequence::create(ColorMatrixOffset::create(0.5, 0, 1, 0, 0, 0, 0), ColorMatrixOffset::create(0.5, 1, 0, 0, 0, 0, 0), ColorMatrixOffset::create(0.5, 0, 0, 0, 1, 0, 0), ColorMatrixOffset::create(0.5, 0, 0, 1, 0, 0, 0), ColorMatrixOffset::create(0.5, 0, 0, 0, 0, 0, 1), ColorMatrixOffset::create(0.5, 0, 0, 0, 0, 1, 0), nullptr)));
    
    spr3->runAction(RepeatForever::create(Sequence::create(ColorMatrixBrightness::create(1, 0, 1), ColorMatrixBrightness::create(1, 1, 0), ColorMatrixBrightness::create(1, 0, -1), ColorMatrixBrightness::create(1, -1, 0), nullptr)));
    
    spr4->runAction(RepeatForever::create(Sequence::create(ColorMatrixSaturation::create(1, 1, 0), DelayTime::create(1), ColorMatrixSaturation::create(1, 0, 1), nullptr)));

    spr5->runAction(RepeatForever::create(Sequence::create(ColorMatrixContrast::create(1, 1, 0), DelayTime::create(1), ColorMatrixContrast::create(1, 0, 1), nullptr)));
    
    spr6->runAction(RepeatForever::create(Sequence::create(ColorMatrixThreshold::create(1, 0, 1), ColorMatrixThreshold::create(1, 1, 0), ColorMatrixThreshold::create(1, 0, -1), ColorMatrixThreshold::create(1, -1, 0), nullptr)));
    
    spr7->runAction(RepeatForever::create(Sequence::create(ColorMatrixHUE::create(1, 0, 1), ColorMatrixHUE::create(1, 1, 0), ColorMatrixHUE::create(1, 0, -1), ColorMatrixHUE::create(1, -1, 0), nullptr)));
    
    spr8->setNeedResetColorMatrixAfterDraw(true);
    spr8->runAction(RepeatForever::create(Sequence::create(ColorMatrixHUE::create(1, 0, 1, true), ColorMatrixHUE::create(1, 1, 0, true), ColorMatrixHUE::create(1, 0, -1, true), ColorMatrixHUE::create(1, -1, 0, true), nullptr)));
    spr8->runAction(RepeatForever::create(Sequence::create(ColorMatrixBrightness::create(1, 0, 1, true), ColorMatrixBrightness::create(1, 1, 0, true), nullptr)));

    spr9->setNeedResetColorMatrixAfterDraw(true);
    ColorMatrixSetNeedResetColorMatrix* enableReset = ColorMatrixSetNeedResetColorMatrix::create(true);
    ColorMatrixSetNeedResetColorMatrix* disableReset = enableReset->reverse();
    
    spr9->runAction(RepeatForever::create(Sequence::create(ColorMatrixHUE::create(1, 0, 1, true), DelayTime::create(1), ColorMatrixHUE::create(1, 1, 0, true), nullptr)));
    spr9->runAction(RepeatForever::create(Sequence::create(ColorMatrixBrightness::create(1, 0, 0.5, true), disableReset, ColorMatrixInversion::create(), DelayTime::create(1), enableReset, ColorMatrixBrightness::create(1, 0.5, 0, true), nullptr)));
    
    
    // MonkVG test
    vgCreateContextMNK( 1136, 640, VG_RENDERING_BACKEND_TYPE_OPENGLES20 );
    
    // create a paint
    _paint = vgCreatePaint();
    vgSetPaint(_paint, VG_FILL_PATH );
    
    VGfloat color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    vgSetParameterfv(_paint, VG_PAINT_COLOR, 4, &color[0]);
    
    _path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,1,0,0,0, VG_PATH_CAPABILITY_ALL);
    vguRect( _path, 50.0f, 50.0f, 90.0f, 50.0f );
    
    vgSetf( VG_STROKE_LINE_WIDTH, 7.0f );
    
    _lineHeight = 74;	// hardwired.  todo: read from file
    
    // create a path for linear gradient
    _linearGradientPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,1,0,0,0, VG_PATH_CAPABILITY_ALL);
    vguRect( _linearGradientPath, 0, 0, 120.0f, 40.0f );
    
    // create a linear gradient paint to apply to the path
    _linearGradientPaint = vgCreatePaint();
    vgSetParameteri(_linearGradientPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_LINEAR_GRADIENT);
    
    // A linear gradient needs start and end points that describe orientation
    // and length of the gradient.
    float afLinearGradientPoints[4] = {
        0.0f, 0.0f,
        120.0f, 0.0f
    };
    vgSetParameterfv(_linearGradientPaint, VG_PAINT_LINEAR_GRADIENT, 4, afLinearGradientPoints);
    
    // Now we have to specify the colour ramp. It is described by "stops" that
    // are given as premultiplied sRGBA colour at a position between 0 and 1.
    // Between these stops, the colour is linearly interpolated.
    // This colour ramp goes from red to green to blue, all opaque.
    float stops[3][5] = {
        {0.0f,	1.0f, 0.0f, 0.0f, 1.0f},
        {0.5f,	0.0f, 1.0f, 0.0f, 0.8f},
        {1.0f,	0.0f, 0.0f, 1.0f, 0.4f}
    };
    vgSetParameterfv(_linearGradientPaint, VG_PAINT_COLOR_RAMP_STOPS, 15, &stops[0][0]);
    
    // setup radial gradient
    _radialGradientPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,1,0,0,0, VG_PATH_CAPABILITY_ALL);
    vguEllipse( _radialGradientPath, 0, 0, 90.0f, 50.0f );
    
    
    _radialGradientPaint = vgCreatePaint();
    vgSetParameteri(_radialGradientPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_RADIAL_GRADIENT);
    float afRadialGradient[5] = {45,25,45,25,45.0f };	// { cx, cy, fx, fy, r }.
    vgSetParameterfv(_radialGradientPaint, VG_PAINT_RADIAL_GRADIENT, 5, afRadialGradient);
    vgSetParameterfv(_radialGradientPaint, VG_PAINT_COLOR_RAMP_STOPS, 15, &stops[0][0]);
    
    return true;
}


#pragma mark - Update

void CCColorMatrixFunctionalTestScene::update (float delta) {
    static float f = 0;
    f += delta;
    float n = (1 + sinf(f)) / 2; // (0~1)
    float n2 = sinf(f); // (-1~1)
    
    ColorMatrix4x4 m;
    
    m = CCColorMatrixMakeBrightness(n2);
    spr1->setColorMatrix(m);
    
    m = CCColorMatrixMakeScale(1, n, 1);
    spr2->setColorMatrix(m);
    
    m = CCColorMatrixMakeOffset(0, n2, 0);
    spr3->setColorMatrix(m);
    
    m = CCColorMatrixMakeInversion();
    spr4->setColorMatrix(m);
    
    m = CCColorMatrixMakeSaturation(n);
    spr5->setColorMatrix(m);
    
    m = CCColorMatrixMakeContrast(n);
    spr6->setColorMatrix(m);
    
    m = CCColorMatrixMakeThreshold(n2);
    spr7->setColorMatrix(m);
    
    m = CCColorMatrixMakeHUE(n);
    spr8->setColorMatrix(m);
    
    // test matrix concat
    ColorMatrix4x4 cmat4_R = CCColorMatrixMakeIdentity();
    ColorMatrix4x4 cmat4 = CCColorMatrixMakeIdentity();
    
    cmat4 = CCColorMatrixMakeInversion();
    cmat4_R = CCColorMatrixConcat(&cmat4, &cmat4_R);
    cmat4 = CCColorMatrixMakeSaturation(n);
    cmat4_R = CCColorMatrixConcat(&cmat4, &cmat4_R);
    
    spr9->setColorMatrix(cmat4_R);
}


#pragma mark - Draw

void CCColorMatrixFunctionalTestScene::draw () {
    _customRenderCommand.init(_globalZOrder);
    _customRenderCommand.func = CC_CALLBACK_0(CCColorMatrixFunctionalTestScene::render, this);
    Director::getInstance()->getRenderer()->addCommand(&_customRenderCommand);
}

void CCColorMatrixFunctionalTestScene::render () {
    // get the width and height of the screen
    VGint backingWidth = vgGeti( VG_SURFACE_WIDTH_MNK );
    VGint backingHeight = vgGeti( VG_SURFACE_HEIGHT_MNK );

//    CCLOG("backingWidth:%i backingHeight:%i", backingWidth, backingHeight);
    
//    VGfloat clearColor[] = {1,1,1,1};
//	vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
//	vgClear(0,0,backingWidth,backingHeight);
	
	/// draw the basic path
//	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
//	vgLoadIdentity();
//	vgTranslate( backingWidth/2, backingHeight/2 );
	vgSetPaint( _paint, VG_STROKE_PATH );
	vgDrawPath( _path, VG_STROKE_PATH );
    
	// draw the gradient path
//	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
//	vgLoadIdentity();
//	vgTranslate( backingWidth/2, backingHeight/2 );
	vgSetPaint( _linearGradientPaint, VG_FILL_PATH );
	vgDrawPath( _linearGradientPath, VG_FILL_PATH );
	
	// draw radial gradient
//	vgLoadIdentity();
//	vgTranslate( 50, backingHeight/2 + 20 );
	vgSetPaint( _radialGradientPaint, VG_FILL_PATH );
	vgDrawPath( _radialGradientPath, VG_FILL_PATH );
}


#pragma mark - Touch callback

void CCColorMatrixFunctionalTestScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *event) {
    
}

void CCColorMatrixFunctionalTestScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *event) {
}

void CCColorMatrixFunctionalTestScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *event) {
}

void CCColorMatrixFunctionalTestScene::onTouchesCancelled(const std::vector<Touch*>& touches, Event *event) {
}
