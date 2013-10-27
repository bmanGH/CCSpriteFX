//
//  CCActionTextureTransform.cpp
//  CCSpriteFX
//
//  Created by bman on 10/25/13.
//
//

#include "CCActionTextureTransform.h"
#include "CCTextureTransformProtocol.h"

NS_CC_EXT_BEGIN


#pragma mark - TexAnchorMoveBy

TexAnchorMoveBy* TexAnchorMoveBy::create (float d, float deltaX, float deltaY) {
    TexAnchorMoveBy* ret = new TexAnchorMoveBy();
	if (ret->initWithDuration(d, deltaX, deltaY))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

TexAnchorMoveBy::TexAnchorMoveBy ()
: _startX(0), _startY(0), _deltaX(0), _deltaY(0) {
}

TexAnchorMoveBy::~TexAnchorMoveBy () {
}

bool TexAnchorMoveBy::initWithDuration (float d, float deltaX, float deltaY) {
    if (ActionInterval::initWithDuration(d)) {
        _deltaX = deltaX;
        _deltaY = deltaY;
        return true;
    }
    return false;
}

void TexAnchorMoveBy::startWithTarget (Node* pTarget) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(pTarget);
    CCAssert(target != nullptr, "CCTextureTransform Actions can only effect on TextureTransformProtocol");
    
    ActionInterval::startWithTarget(pTarget);
    _startX = target->getTexAnchorOffsetX();
    _startY = target->getTexAnchorOffsetY();
}

void TexAnchorMoveBy::update (float time) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(_target);
    target->setTexAnchorOffsetX(_startX + _deltaX * time);
    target->setTexAnchorOffsetY(_startY + _deltaY * time);
}

TexAnchorMoveBy* TexAnchorMoveBy::clone() const {
    return TexAnchorMoveBy::create(_duration, _deltaX, _deltaY);
}

TexAnchorMoveBy* TexAnchorMoveBy::reverse() const {
    return TexAnchorMoveBy::create(_duration, -_deltaX, -_deltaY);
}


#pragma mark - TexAnchorMoveTo

TexAnchorMoveTo* TexAnchorMoveTo::create (float d, float x, float y) {
    TexAnchorMoveTo* ret = new TexAnchorMoveTo();
	if (ret->initWithDuration(d, x, y))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

TexAnchorMoveTo::TexAnchorMoveTo ()
: _targetX(0), _targetY(0) {
}

TexAnchorMoveTo::~TexAnchorMoveTo () {
}

bool TexAnchorMoveTo::initWithDuration (float d, float x, float y) {
    if (ActionInterval::initWithDuration(d)) {
        _targetX = x;
        _targetY = y;
        return true;
    }
    return false;
}

void TexAnchorMoveTo::startWithTarget (Node* pTarget) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(pTarget);
    CCASSERT(target != nullptr, "CCTextureTransform Actions can only effect on TextureTransformProtocol");
    
    ActionInterval::startWithTarget(pTarget);
    _startX = target->getTexAnchorOffsetX();
    _startY = target->getTexAnchorOffsetY();
    _deltaX = _targetX - _startX;
    _deltaY = _targetY - _startY;
}

TexAnchorMoveTo* TexAnchorMoveTo::clone() const {
    return TexAnchorMoveTo::create(_duration, _targetX, _targetY);
}

TexAnchorMoveTo* TexAnchorMoveTo::reverse() const {
	CCASSERT(false, "TexAnchorMoveTo doesn't support the 'reverse' method");
    return nullptr;
}


#pragma mark - TexMoveBy

TexMoveBy* TexMoveBy::create (float d, float deltaX, float deltaY) {
    TexMoveBy* ret = new TexMoveBy();
	if (ret->initWithDuration(d, deltaX, deltaY))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

TexMoveBy::TexMoveBy ()
: _startX(0), _startY(0), _deltaX(0), _deltaY(0) {
}

TexMoveBy::~TexMoveBy () {
}

bool TexMoveBy::initWithDuration (float d, float deltaX, float deltaY) {
    if (ActionInterval::initWithDuration(d)) {
        _deltaX = deltaX;
        _deltaY = deltaY;
        return true;
    }
    return false;
}

void TexMoveBy::startWithTarget (Node* pTarget) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(pTarget);
    CCAssert(target != nullptr, "CCTextureTransform Actions can only effect on TextureTransformProtocol");
    
    ActionInterval::startWithTarget(pTarget);
    _startX = target->getTexOffsetX();
    _startY = target->getTexOffsetX();
}

void TexMoveBy::update (float time) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(_target);
    target->setTexOffsetX(_startX + _deltaX * time);
    target->setTexOffsetY(_startY + _deltaY * time);
}

TexMoveBy* TexMoveBy::clone() const {
    return TexMoveBy::create(_duration, _deltaX, _deltaY);
}

TexMoveBy* TexMoveBy::reverse() const {
    return TexMoveBy::create(_duration, -_deltaX, -_deltaY);
}


#pragma mark - TexMoveTo

TexMoveTo* TexMoveTo::create (float d, float x, float y) {
    TexMoveTo* ret = new TexMoveTo();
	if (ret->initWithDuration(d, x, y))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

TexMoveTo::TexMoveTo ()
: _targetX(0), _targetY(0) {
}

TexMoveTo::~TexMoveTo () {
}

bool TexMoveTo::initWithDuration (float d, float x, float y) {
    if (ActionInterval::initWithDuration(d)) {
        _targetX = x;
        _targetY = y;
        return true;
    }
    return false;
}

void TexMoveTo::startWithTarget (Node* pTarget) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(pTarget);
    CCASSERT(target != nullptr, "CCTextureTransform Actions can only effect on TextureTransformProtocol");
    
    ActionInterval::startWithTarget(pTarget);
    _startX = target->getTexOffsetX();
    _startY = target->getTexOffsetY();
    _deltaX = _targetX - _startX;
    _deltaY = _targetY - _startY;
}

TexMoveTo* TexMoveTo::clone() const {
    return TexMoveTo::create(_duration, _targetX, _targetY);
}

TexMoveTo* TexMoveTo::reverse() const {
	CCASSERT(false, "TexMoveTo doesn't support the 'reverse' method");
    return nullptr;
}


#pragma mark - TexRotateBy

TexRotateBy* TexRotateBy::create(float d, float deltaRot) {
    TexRotateBy* ret = new TexRotateBy();
	if (ret->initWithDuration(d, deltaRot))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

TexRotateBy::TexRotateBy ()
: _deltaRot(0) {
}

TexRotateBy::~TexRotateBy () {
}

bool TexRotateBy::initWithDuration(float d, float deltaRot) {
    if (ActionInterval::initWithDuration(d)) {
        _deltaRot = deltaRot;
        return true;
    }
    return false;
}

void TexRotateBy::startWithTarget (Node* pTarget) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(pTarget);
    CCAssert(target != nullptr, "CCTextureTransform Actions can only effect on TextureTransformProtocol");
    
    ActionInterval::startWithTarget(pTarget);
    _startRot = target->getTexRotation();
}

void TexRotateBy::update (float time) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(_target);
    target->setTexRotation(_startRot + _deltaRot * time);
}

TexRotateBy* TexRotateBy::clone() const {
    return TexRotateBy::create(_duration, _deltaRot);
}

TexRotateBy* TexRotateBy::reverse() const {
    return TexRotateBy::create(_duration, -_deltaRot);
}


#pragma mark - TexRotateTo

TexRotateTo* TexRotateTo::create(float d, float rot) {
    TexRotateTo* ret = new TexRotateTo();
	if (ret->initWithDuration(d, rot))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

TexRotateTo::TexRotateTo ()
: _targetRot(0) {
}

TexRotateTo::~TexRotateTo () {
}

bool TexRotateTo::initWithDuration(float d, float rot) {
    if (ActionInterval::initWithDuration(d)) {
        _targetRot = rot;
        return true;
    }
    return false;
}

void TexRotateTo::startWithTarget (Node* pTarget) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(pTarget);
    CCAssert(target != nullptr, "CCTextureTransform Actions can only effect on TextureTransformProtocol");
    
    ActionInterval::startWithTarget(pTarget);
    
    // clamp into one cycle
    _startRot = target->getTexRotation();
    if (_startRot > 0)
        _startRot = fmodf(_startRot, 360.0f);
    else
        _startRot = fmodf(_startRot, -360.0f);
    
    // turning by shortest way
    _deltaRot = _targetRot - _startRot;
    if (_deltaRot > 180)
        _deltaRot -= 360;
    if (_deltaRot < -180)
        _deltaRot += 360;
}

TexRotateTo* TexRotateTo::clone() const {
    return TexRotateTo::create(_duration, _targetRot);
}

TexRotateTo* TexRotateTo::reverse() const {
	CCASSERT(false, "TexRotateTo doesn't support the 'reverse' method");
    return nullptr;
}


#pragma mark - TexScaleBy

TexScaleBy* TexScaleBy::create(float d, float deltaSX, float deltaSY) {
    TexScaleBy* ret = new TexScaleBy();
	if (ret->initWithDuration(d, deltaSX, deltaSY))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

TexScaleBy::TexScaleBy ()
: _deltaSX(0), _deltaSY(0) {
}

TexScaleBy::~TexScaleBy () {
}

bool TexScaleBy::initWithDuration(float d, float deltaSX, float deltaSY) {
    if (ActionInterval::initWithDuration(d)) {
        _deltaSX = deltaSX;
        _deltaSY = deltaSY;
        return true;
    }
    return false;
}

void TexScaleBy::startWithTarget (Node* pTarget) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(pTarget);
    CCAssert(target != nullptr, "CCTextureTransform Actions can only effect on TextureTransformProtocol");
    
    ActionInterval::startWithTarget(pTarget);
    _startSX = target->getTexScaleX();
    _startSY = target->getTexScaleY();
}

void TexScaleBy::update (float time) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(_target);
    target->setTexScaleX(_startSX + _deltaSX * time);
    target->setTexScaleY(_startSY + _deltaSY * time);
}

TexScaleBy* TexScaleBy::clone() const {
    return TexScaleBy::create(_duration, _deltaSX, _deltaSY);
}

TexScaleBy* TexScaleBy::reverse() const {
    return TexScaleBy::create(_duration, -_deltaSX, -_deltaSY);
}


#pragma mark - TexScaleTo

TexScaleTo* TexScaleTo::create(float d, float sx, float sy) {
    TexScaleTo* ret = new TexScaleTo();
	if (ret->initWithDuration(d, sx, sy))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

TexScaleTo::TexScaleTo ()
: _targetSX(0), _targetSY(0) {
}

TexScaleTo::~TexScaleTo () {
}

bool TexScaleTo::initWithDuration(float d, float sx, float sy) {
    if (ActionInterval::initWithDuration(d)) {
        _targetSX = sx;
        _targetSY = sy;
        return true;
    }
    return false;
}

void TexScaleTo::startWithTarget (Node* pTarget) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(pTarget);
    CCAssert(target != nullptr, "CCTextureTransform Actions can only effect on TextureTransformProtocol");
    
    ActionInterval::startWithTarget(pTarget);
    _startSX = target->getTexScaleX();
    _startSY = target->getTexScaleY();
    _deltaSX = _targetSX - _startSX;
    _deltaSY = _targetSY - _startSY;
}

TexScaleTo* TexScaleTo::clone() const {
    return TexScaleTo::create(_duration, _targetSX, _targetSY);
}

TexScaleTo* TexScaleTo::reverse() const {
	CCASSERT(false, "TexScaleTo doesn't support the 'reverse' method");
    return nullptr;
}


#pragma mark - TexSkewBy

TexSkewBy* TexSkewBy::create(float d, float deltaKX, float deltaKY) {
    TexSkewBy* ret = new TexSkewBy();
	if (ret->initWithDuration(d, deltaKX, deltaKY))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

TexSkewBy::TexSkewBy ()
: _deltaKX(0), _deltaKY(0) {
}

TexSkewBy::~TexSkewBy () {
}

bool TexSkewBy::initWithDuration(float d, float deltaKX, float deltaKY) {
    if (ActionInterval::initWithDuration(d)) {
        _deltaKX = deltaKX;
        _deltaKY = deltaKY;
        return true;
    }
    return false;
}

void TexSkewBy::startWithTarget (Node* pTarget) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(pTarget);
    CCAssert(target != nullptr, "CCTextureTransform Actions can only effect on TextureTransformProtocol");
    
    ActionInterval::startWithTarget(pTarget);
    _startKX = target->getTexSkewX();
    _startKY = target->getTexSkewY();
}

void TexSkewBy::update (float time) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(_target);
    target->setTexSkewX(_startKX + _deltaKX * time);
    target->setTexSkewY(_startKY + _deltaKY * time);
}

TexSkewBy* TexSkewBy::clone() const {
    return TexSkewBy::create(_duration, _deltaKX, _deltaKY);
}

TexSkewBy* TexSkewBy::reverse() const {
    return TexSkewBy::create(_duration, -_deltaKX, -_deltaKY);
}


#pragma mark - TexSkewTo

TexSkewTo* TexSkewTo::create(float d, float kx, float ky) {
    TexSkewTo* ret = new TexSkewTo();
	if (ret->initWithDuration(d, kx, ky))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

TexSkewTo::TexSkewTo ()
: _targetKX(0), _targetKY(0) {
}

TexSkewTo::~TexSkewTo () {
}

bool TexSkewTo::initWithDuration(float d, float kx, float ky) {
    if (ActionInterval::initWithDuration(d)) {
        _targetKX = kx;
        _targetKY = ky;
        return true;
    }
    return false;
}

void TexSkewTo::startWithTarget (Node* pTarget) {
    TextureTransformProtocol* target = dynamic_cast<TextureTransformProtocol*>(pTarget);
    CCAssert(target != nullptr, "CCTextureTransform Actions can only effect on TextureTransformProtocol");
    
    ActionInterval::startWithTarget(pTarget);
    
    // clamp into one cycle
    _startKX = target->getTexSkewX();
    if (_startKX > 0)
        _startKX = fmodf(_startKX, 360.0f);
    else
        _startKX = fmodf(_startKX, -360.0f);
    
    // turning by shortest way
    _deltaKX = _targetKX - _startKX;
    if (_deltaKX > 180)
        _deltaKX -= 360;
    if (_deltaKX < -180)
        _deltaKX += 360;
    
    // clamp into one cycle
    _startKY = target->getTexSkewY();
    if (_startKY > 0)
        _startKY = fmodf(_startKY, 360.0f);
    else
        _startKY = fmodf(_startKY, -360.0f);
    
    // turning by shortest way
    _deltaKY = _targetKY - _startKY;
    if (_deltaKY > 180)
        _deltaKY -= 360;
    if (_deltaKY < -180)
        _deltaKY += 360;
}

TexSkewTo* TexSkewTo::clone() const {
    return TexSkewTo::create(_duration, _targetKX, _targetKY);
}

TexSkewTo* TexSkewTo::reverse() const {
	CCASSERT(false, "TexSkewTo doesn't support the 'reverse' method");
    return nullptr;
}


NS_CC_EXT_END
