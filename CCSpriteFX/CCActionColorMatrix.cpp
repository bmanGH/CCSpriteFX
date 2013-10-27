//
//  CCActionColorMatrix.cpp
//  CCSpriteFX
//
//  Created by bman on 7/24/13.
//
//

#include "CCActionColorMatrix.h"
#include "CCColorMatrixProtocol.h"

NS_CC_EXT_BEGIN


#pragma mark - ColorMatrixActionInterval

ColorMatrixActionInterval::ColorMatrixActionInterval ()
: _needConcat(false) {
}

ColorMatrixActionInterval::~ColorMatrixActionInterval () {
}

bool ColorMatrixActionInterval::initWithDuration(float d, bool needConcat) {
    if (ActionInterval::initWithDuration(d)) {
        _needConcat = needConcat;
        return true;
    }
    return false;
}

void ColorMatrixActionInterval::updateTargetColorMatrix (ColorMatrix4x4& cmat) {
    ColorMatrixProtocol* target = dynamic_cast<ColorMatrixProtocol*>(_target);
    if (_needConcat) {
        target->concatColorMatrix(cmat);
    }
    else {
        target->setColorMatrix(cmat);
    }
}

void ColorMatrixActionInterval::startWithTarget (Node *pTarget) {
    ColorMatrixProtocol* target = dynamic_cast<ColorMatrixProtocol*>(pTarget);
    CCASSERT(target != nullptr, "CCColorMatrix Actions can only effect on ColorMatrixProtocol");
    
    ActionInterval::startWithTarget(pTarget);
}


#pragma mark - ColorMatrixActionInstant

ColorMatrixActionInstant::ColorMatrixActionInstant ()
: _needConcat(false) {
}

ColorMatrixActionInstant::~ColorMatrixActionInstant () {
}

bool ColorMatrixActionInstant::init (bool needConcat) {
    _needConcat = needConcat;
    return true;
}

void ColorMatrixActionInstant::updateTargetColorMatrix (ColorMatrix4x4& cmat) {
    ColorMatrixProtocol* target = dynamic_cast<ColorMatrixProtocol*>(_target);
    if (_needConcat) {
        target->concatColorMatrix(cmat);
    }
    else {
        target->setColorMatrix(cmat);
    }
}

void ColorMatrixActionInstant::startWithTarget (Node *pTarget) {
    ColorMatrixProtocol* target = dynamic_cast<ColorMatrixProtocol*>(pTarget);
    CCASSERT(target != nullptr, "CCColorMatrix Actions can only effect on ColorMatrixProtocol");
    
    CCActionInstant::startWithTarget(pTarget);
}


#pragma mark - ColorMatrixScale

ColorMatrixScale* ColorMatrixScale::create (float d, float fromR, float toR, float fromG, float toG, float fromB, float toB, bool needConcat) {
    ColorMatrixScale* ret = new ColorMatrixScale();
	if (ret->initWithDuration(d, fromR, toR, fromG, toG, fromB, toB, needConcat))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

ColorMatrixScale::ColorMatrixScale ()
: _fromR(0), _toR(0), _fromG(0), _toG(0), _fromB(0), _toB(0) {
}

ColorMatrixScale::~ColorMatrixScale () {
}

bool ColorMatrixScale::initWithDuration (float d, float fromR, float toR, float fromG, float toG, float fromB, float toB, bool needConcat)
{
    if (ColorMatrixActionInterval::initWithDuration(d, needConcat)) {
        _fromR = fromR;
        _toR = toR;
        _fromG = fromG;
        _toG = toG;
        _fromB = fromB;
        _toB = toB;
        return true;
    }
    return false;
}

void ColorMatrixScale::update (float time) {
    float r = _fromR + time * (_toR - _fromR);
    float g = _fromG + time * (_toG - _fromG);
    float b = _fromB + time * (_toB - _fromB);
    ColorMatrix4x4 cmat = CCColorMatrixMakeScale(r, g, b);
    this->updateTargetColorMatrix(cmat);
}

ColorMatrixScale* ColorMatrixScale::clone() const {
    return ColorMatrixScale::create(_duration, _fromR, _toR, _fromG, _toG, _fromB, _toB, _needConcat);
}

ColorMatrixScale* ColorMatrixScale::reverse() const {
    return ColorMatrixScale::create(_duration, _toR, _fromR, _toG, _fromG, _toB, _fromB, _needConcat);
}


#pragma mark - ColorMatrixOffset

ColorMatrixOffset* ColorMatrixOffset::create (float d, float fromR, float toR, float fromG, float toG, float fromB, float toB, bool needConcat) {
    ColorMatrixOffset* ret = new ColorMatrixOffset();
	if (ret->initWithDuration(d, fromR, toR, fromG, toG, fromB, toB, needConcat))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

ColorMatrixOffset::ColorMatrixOffset ()
: _fromR(0), _toR(0), _fromG(0), _toG(0), _fromB(0), _toB(0) {
}

ColorMatrixOffset::~ColorMatrixOffset () {
}

bool ColorMatrixOffset::initWithDuration (float d, float fromR, float toR, float fromG, float toG, float fromB, float toB, bool needConcat) {
    if (ColorMatrixActionInterval::initWithDuration(d, needConcat)) {
        _fromR = fromR;
        _toR = toR;
        _fromG = fromG;
        _toG = toG;
        _fromB = fromB;
        _toB = toB;
        return true;
    }
    return false;
}

void ColorMatrixOffset::update (float time) {
    float r = _fromR + time * (_toR - _fromR);
    float g = _fromG + time * (_toG - _fromG);
    float b = _fromB + time * (_toB - _fromB);
    ColorMatrix4x4 cmat = CCColorMatrixMakeOffset(r, g, b);
    this->updateTargetColorMatrix(cmat);
}

ColorMatrixOffset* ColorMatrixOffset::clone() const {
    return ColorMatrixOffset::create(_duration, _fromR, _toR, _fromG, _toG, _fromB, _toB, _needConcat);
}

ColorMatrixOffset* ColorMatrixOffset::reverse() const {
    return ColorMatrixOffset::create(_duration, _toR, _fromR, _toG, _fromG, _toB, _fromB, _needConcat);
}


#pragma mark - ColorMatrixBrightness

ColorMatrixBrightness* ColorMatrixBrightness::create(float d, float from, float to, bool needConcat) {
    ColorMatrixBrightness* ret = new ColorMatrixBrightness();
	if (ret->initWithDuration(d, from, to, needConcat))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

ColorMatrixBrightness::ColorMatrixBrightness ()
: _from(0), _to(0) {
    
}

ColorMatrixBrightness::~ColorMatrixBrightness () {
}

bool ColorMatrixBrightness::initWithDuration(float d, float from, float to, bool needConcat) {
    if (ColorMatrixActionInterval::initWithDuration(d, needConcat)) {
        _from = from;
        _to = to;
        return true;
    }
    return false;
}

void ColorMatrixBrightness::update (float time) {
    float n = _from + time * (_to - _from);
    ColorMatrix4x4 cmat = CCColorMatrixMakeBrightness(n);
    this->updateTargetColorMatrix(cmat);
}

ColorMatrixBrightness* ColorMatrixBrightness::clone() const {
    return ColorMatrixBrightness::create(_duration, _from, _to, _needConcat);
}

ColorMatrixBrightness* ColorMatrixBrightness::reverse() const {
    return ColorMatrixBrightness::create(_duration, _to, _from, _needConcat);
}


#pragma mark - ColorMatrixSaturation

ColorMatrixSaturation* ColorMatrixSaturation::create(float d, float from, float to, bool needConcat) {
    ColorMatrixSaturation* ret = new ColorMatrixSaturation();
	if (ret->initWithDuration(d, from, to, needConcat))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

ColorMatrixSaturation::ColorMatrixSaturation ()
: _from(0), _to(0) {
}

ColorMatrixSaturation::~ColorMatrixSaturation () {
}

bool ColorMatrixSaturation::initWithDuration (float d, float from, float to, bool needConcat) {
    if (ColorMatrixActionInterval::initWithDuration(d, needConcat)) {
        _from = from;
        _to = to;
        return true;
    }
    return false;
}

void ColorMatrixSaturation::update (float time) {
    float n = _from + time * (_to - _from);
    ColorMatrix4x4 cmat = CCColorMatrixMakeSaturation(n);
    this->updateTargetColorMatrix(cmat);
}

ColorMatrixSaturation* ColorMatrixSaturation::clone() const {
    return ColorMatrixSaturation::create(_duration, _from, _to, _needConcat);
}

ColorMatrixSaturation* ColorMatrixSaturation::reverse() const {
    return ColorMatrixSaturation::create(_duration, _to, _from, _needConcat);
}


#pragma mark - ColorMatrixContrast

ColorMatrixContrast* ColorMatrixContrast::create(float d, float from, float to, bool needConcat) {
    ColorMatrixContrast* ret = new ColorMatrixContrast();
	if (ret->initWithDuration(d, from, to, needConcat))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

ColorMatrixContrast::ColorMatrixContrast ()
: _from(0), _to(0) {
}

ColorMatrixContrast::~ColorMatrixContrast () {
}

bool ColorMatrixContrast::initWithDuration (float d, float from, float to, bool needConcat) {
    if (ColorMatrixActionInterval::initWithDuration(d, needConcat)) {
        _from = from;
        _to = to;
        return true;
    }
    return false;
}

void ColorMatrixContrast::update (float time) {
    float n = _from + time * (_to - _from);
    ColorMatrix4x4 cmat = CCColorMatrixMakeContrast(n);
    this->updateTargetColorMatrix(cmat);
}

ColorMatrixContrast* ColorMatrixContrast::clone() const {
    return ColorMatrixContrast::create(_duration, _from, _to, _needConcat);
}

ColorMatrixContrast* ColorMatrixContrast::reverse() const {
    return ColorMatrixContrast::create(_duration, _to, _from, _needConcat);
}


#pragma mark - ColorMatrixThreshold

ColorMatrixThreshold* ColorMatrixThreshold::create (float d, float from, float to, bool needConcat) {
    ColorMatrixThreshold* ret = new ColorMatrixThreshold();
	if (ret->initWithDuration(d, from, to, needConcat))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

ColorMatrixThreshold::ColorMatrixThreshold ()
: _from(0), _to(0) {
}

ColorMatrixThreshold::~ColorMatrixThreshold () {
}

bool ColorMatrixThreshold::initWithDuration (float d, float from, float to, bool needConcat) {
    if (ColorMatrixActionInterval::initWithDuration(d, needConcat)) {
        _from = from;
        _to = to;
        return true;
    }
    return false;
}

void ColorMatrixThreshold::update (float time) {
    float n = _from + time * (_to - _from);
    ColorMatrix4x4 cmat = CCColorMatrixMakeThreshold(n);
    this->updateTargetColorMatrix(cmat);
}

ColorMatrixThreshold* ColorMatrixThreshold::clone() const {
    return ColorMatrixThreshold::create(_duration, _from, _to, _needConcat);
}

ColorMatrixThreshold* ColorMatrixThreshold::reverse() const {
    return ColorMatrixThreshold::create(_duration, _to, _from, _needConcat);
}


#pragma mark - ColorMatrixHUE

ColorMatrixHUE* ColorMatrixHUE::create (float d, float from, float to, bool needConcat) {
    ColorMatrixHUE* ret = new ColorMatrixHUE();
	if (ret->initWithDuration(d, from, to, needConcat))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

ColorMatrixHUE::ColorMatrixHUE ()
: _from(0), _to(0) {
}

ColorMatrixHUE::~ColorMatrixHUE () {
}

bool ColorMatrixHUE::initWithDuration (float d, float from, float to, bool needConcat) {
    if (ColorMatrixActionInterval::initWithDuration(d, needConcat)) {
        _from = from;
        _to = to;
        return true;
    }
    return false;
}

void ColorMatrixHUE::update (float time) {
    float n = _from + time * (_to - _from);
    ColorMatrix4x4 cmat = CCColorMatrixMakeHUE(n);
    this->updateTargetColorMatrix(cmat);
}

ColorMatrixHUE* ColorMatrixHUE::clone() const {
    return ColorMatrixHUE::create(_duration, _from, _to, _needConcat);
}

ColorMatrixHUE* ColorMatrixHUE::reverse() const {
    return ColorMatrixHUE::create(_duration, _to, _from, _needConcat);
}


#pragma mark - ColorMatrixIdentity

ColorMatrixIdentity* ColorMatrixIdentity::create (bool needConcat) {
    ColorMatrixIdentity* ret = new ColorMatrixIdentity();
	if (ret->init(needConcat))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

ColorMatrixIdentity::ColorMatrixIdentity () {
}

ColorMatrixIdentity::~ColorMatrixIdentity () {
}

bool ColorMatrixIdentity::init (bool needConcat) {
    if (ColorMatrixActionInstant::init(needConcat)) {
        return true;
    }
    return false;
}

void ColorMatrixIdentity::update (float time) {
    CC_UNUSED_PARAM(time);
    ColorMatrix4x4 cmat = CCColorMatrixMakeIdentity();
    this->updateTargetColorMatrix(cmat);
}

ColorMatrixIdentity* ColorMatrixIdentity::clone() const {
    return ColorMatrixIdentity::create(_needConcat);
}

ColorMatrixActionInstant* ColorMatrixIdentity::reverse() const {
    return ColorMatrixInversion::create(_needConcat);
}


#pragma mark - ColorMatrixInversion

ColorMatrixInversion* ColorMatrixInversion::create (bool needConcat) {
    ColorMatrixInversion* ret = new ColorMatrixInversion();
	if (ret->init(needConcat))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

ColorMatrixInversion::ColorMatrixInversion () {
}

ColorMatrixInversion::~ColorMatrixInversion () {
}

bool ColorMatrixInversion::init (bool needConcat) {
    if (ColorMatrixActionInstant::init(needConcat)) {
        return true;
    }
    return false;
}

void ColorMatrixInversion::update (float time) {
    CC_UNUSED_PARAM(time);
    ColorMatrix4x4 cmat = CCColorMatrixMakeInversion();
    this->updateTargetColorMatrix(cmat);
}

ColorMatrixInversion* ColorMatrixInversion::clone() const {
    return ColorMatrixInversion::create(_needConcat);
}

ColorMatrixActionInstant* ColorMatrixInversion::reverse() const {
    return ColorMatrixIdentity::create(_needConcat);
}


#pragma mark - ColorMatrixSetNeedResetColorMatrix

ColorMatrixSetNeedResetColorMatrix* ColorMatrixSetNeedResetColorMatrix::create (bool needResetColorMatrix) {
    ColorMatrixSetNeedResetColorMatrix* ret = new ColorMatrixSetNeedResetColorMatrix();
	if (ret->init(needResetColorMatrix))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

ColorMatrixSetNeedResetColorMatrix::ColorMatrixSetNeedResetColorMatrix ()
: _needResetColorMatrix(false) {
}

ColorMatrixSetNeedResetColorMatrix::~ColorMatrixSetNeedResetColorMatrix () {
}

bool ColorMatrixSetNeedResetColorMatrix::init (bool needResetColorMatrix) {
    _needResetColorMatrix = needResetColorMatrix;
    return true;
}

void ColorMatrixSetNeedResetColorMatrix::startWithTarget (Node *pTarget) {
    ColorMatrixProtocol* target = dynamic_cast<ColorMatrixProtocol*>(pTarget);
    CCASSERT(target != nullptr, "CCColorMatrix Actions can only effect on ColorMatrixProtocol");
    
    CCActionInstant::startWithTarget(pTarget);
}

void ColorMatrixSetNeedResetColorMatrix::update (float time) {
    ColorMatrixProtocol* target = dynamic_cast<ColorMatrixProtocol*>(_target);
    target->setNeedResetColorMatrixAfterDraw(_needResetColorMatrix);
}

ColorMatrixSetNeedResetColorMatrix* ColorMatrixSetNeedResetColorMatrix::clone() const {
    return ColorMatrixSetNeedResetColorMatrix::create(_needResetColorMatrix);
}

ColorMatrixSetNeedResetColorMatrix* ColorMatrixSetNeedResetColorMatrix::reverse() const {
    return ColorMatrixSetNeedResetColorMatrix::create(!_needResetColorMatrix);
}


NS_CC_EXT_END
