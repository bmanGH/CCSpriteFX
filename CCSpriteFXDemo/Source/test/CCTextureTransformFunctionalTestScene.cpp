#include "CCTextureTransformFunctionalTestScene.h"


Scene* CCTextureTransformFunctionalTestScene::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    CCTextureTransformFunctionalTestScene *layer = CCTextureTransformFunctionalTestScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

CCTextureTransformFunctionalTestScene::~CCTextureTransformFunctionalTestScene () {
    
}

bool CCTextureTransformFunctionalTestScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    spr1 = SpriteFX::create("image/pot_icon.png");
    spr1->setScale(0.5);
    spr1->setTextureWrapRepeat();
    spr1->setPosition(Point(winSize.width / 4, winSize.height / 3));
    this->addChild(spr1);
    
    spr2 = SpriteFX::create("image/pot_icon.png");
    spr2->setScale(0.5);
    spr2->setTextureWrapRepeat();
    spr2->setPosition(Point(winSize.width / 4 * 2, winSize.height / 3));
    this->addChild(spr2);
    
    spr3 = SpriteFX::create("image/pot_icon.png");
    spr3->setScale(0.5);
    spr3->setTextureWrapRepeat();
    spr3->setPosition(Point(winSize.width / 4 * 3, winSize.height / 3));
    this->addChild(spr3);
    
    spr4 = SpriteFX::create("image/pot_icon.png");
    spr4->setScale(0.5);
    spr4->setTextureWrapRepeat();
    spr4->setPosition(Point(winSize.width / 4, winSize.height / 3 * 2));
    this->addChild(spr4);
    
    spr5 = SpriteFX::create("image/pot_icon.png");
    spr5->setScale(0.5);
    spr5->setTextureWrapRepeat();
    spr5->setPosition(Point(winSize.width / 4 * 2, winSize.height / 3 * 2));
    this->addChild(spr5);
    
    spr6 = SpriteFX::create("image/pot_icon.png");
    spr6->setScale(0.5);
    spr6->setTextureWrapRepeat();
    spr6->setPosition(Point(winSize.width / 4 * 3, winSize.height / 3 * 2));
    this->addChild(spr6);
    
    // TextureTransform test
//    this->scheduleUpdate();
    
    // TextureTransform Actions test
    spr1->runAction(RepeatForever::create(TexAnchorMoveBy::create(1.5, 1, 1)));
    
    spr2->runAction(RepeatForever::create(TexMoveBy::create(1.5, 1, 1)));
    
    spr3->runAction(RepeatForever::create(TexRotateBy::create(1, 60)));
    
    spr4->runAction(RepeatForever::create(Sequence::create(TexScaleTo::create(1.5, 3, 3),
                                                           TexScaleTo::create(1.5, 1, 1),
                                                           nullptr)));
    
    spr5->runAction(RepeatForever::create(Sequence::create(TexSkewTo::create(1.5, 15, 15),
                                                           TexSkewTo::create(1.5, -15, -15),
                                                           nullptr)));
    
    spr6->runAction(RepeatForever::create(Spawn::create(TexRotateBy::create(3, -45),
                                                        Sequence::create(TexScaleTo::create(1.5, 2, 2),
                                                                         TexScaleTo::create(1.5, 1, 1),
                                                                         nullptr),
                                                        nullptr)));
    
    return true;
}


#pragma mark - Update

void CCTextureTransformFunctionalTestScene::update (float delta) {
    static float f = 0;
    f += delta;
    
    spr1->setTexAnchorOffsetX(f);
    spr1->setTexAnchorOffsetY(f);
    
    spr2->setTexOffsetX(f);
    spr2->setTexOffsetY(f);
    
    spr3->setTexRotation(f * 60);
    
    spr4->setTexScaleX(1 + (0.5 + sinf(f) / 2) * 2);
    spr4->setTexScaleY(1 + (0.5 + sinf(f) / 2) * 2);
    
    spr5->setTexSkewX(0 + (0.5 + sinf(f) / 2) * 30);
    spr5->setTexSkewY(0 + (0.5 + sinf(f) / 2) * 30);
    
    spr6->setTexSkewX(sinf(f * 2) * 15);
    spr6->setTexSkewY(sinf(f * 2) * 15);
    spr6->setSkewX(sinf(f * 2) * -15);
    spr6->setSkewY(sinf(f * 2) * -15);
}


#pragma mark - Draw

void CCTextureTransformFunctionalTestScene::draw () {
    
}


#pragma mark - Touch callback

void CCTextureTransformFunctionalTestScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *event) {
    
}

void CCTextureTransformFunctionalTestScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *event) {
}

void CCTextureTransformFunctionalTestScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *event) {
}

void CCTextureTransformFunctionalTestScene::onTouchesCancelled(const std::vector<Touch*>& touches, Event *event) {
}
