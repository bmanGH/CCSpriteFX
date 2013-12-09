//
//  CCActionTextureTransform.h
//  CCSpriteFX
//
//  Created by bman on 10/25/13.
//
//

#ifndef __CCActionTextureTransform__
#define __CCActionTextureTransform__

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN


/**
 * texture crood
 */
class CC_DLL TexAnchorMoveBy : public ActionInterval {
    
protected:
    float _startX;
    float _startY;
    float _deltaX;
    float _deltaY;
    
public:
    static TexAnchorMoveBy* create (float d, float deltaX, float deltaY);
    
    TexAnchorMoveBy ();
    virtual ~TexAnchorMoveBy ();
    
    bool initWithDuration (float d, float deltaX, float deltaY);
    
    virtual void startWithTarget (Node* pTarget) override;
    virtual void update (float time) override;
    
	virtual TexAnchorMoveBy* clone() const override;
    virtual TexAnchorMoveBy* reverse() const override;
    
};


/**
 * texture crood
 */
class CC_DLL TexAnchorMoveTo : public TexAnchorMoveBy {
    
protected:
    float _targetX;
    float _targetY;
    
public:
    static TexAnchorMoveTo* create (float d, float x, float y);
    
    TexAnchorMoveTo ();
    virtual ~TexAnchorMoveTo ();
    
    bool initWithDuration (float d, float x, float y);
    
    virtual void startWithTarget (Node* pTarget) override;
    
	virtual TexAnchorMoveTo* clone() const override;
    virtual TexAnchorMoveTo* reverse() const override;
    
};


/**
 * texture crood
 */
class CC_DLL TexMoveBy : public ActionInterval {
    
protected:
    float _startX;
    float _startY;
    float _deltaX;
    float _deltaY;
    
public:
    static TexMoveBy* create (float d, float deltaX, float deltaY);
    
    TexMoveBy ();
    virtual ~TexMoveBy ();
    
    bool initWithDuration (float d, float deltaX, float deltaY);
    
    virtual void startWithTarget (Node* pTarget) override;
    virtual void update (float time) override;
    
	virtual TexMoveBy* clone() const override;
    virtual TexMoveBy* reverse() const override;
    
};


/**
 * texture crood
 */
class CC_DLL TexMoveTo : public TexMoveBy {
    
protected:
    float _targetX;
    float _targetY;
    
public:
    static TexMoveTo* create (float d, float x, float y);
    
    TexMoveTo ();
    virtual ~TexMoveTo ();
    
    bool initWithDuration (float d, float x, float y);
    
    virtual void startWithTarget (Node* pTarget) override;
    
	virtual TexMoveTo* clone() const override;
    virtual TexMoveTo* reverse() const override;
    
};


/**
 * clockwise
 */
class CC_DLL TexRotateBy : public ActionInterval {
    
protected:
    float _startRot;
    float _deltaRot;
    
public:
    static TexRotateBy* create (float d, float deltaRot);
    
    TexRotateBy ();
    virtual ~TexRotateBy ();
    
    bool initWithDuration (float d, float deltaRot);
    
    virtual void startWithTarget (Node* pTarget) override;
    virtual void update (float time) override;
    
	virtual TexRotateBy* clone() const override;
    virtual TexRotateBy* reverse() const override;
    
};


/**
 * clockwise
 */
class CC_DLL TexRotateTo : public TexRotateBy {
    
protected:
    float _targetRot;
    
public:
    static TexRotateTo* create (float d, float rot);
    
    TexRotateTo ();
    virtual ~TexRotateTo ();
    
    bool initWithDuration (float d, float rot);
    
    virtual void startWithTarget (Node* pTarget) override;
    
	virtual TexRotateTo* clone() const override;
    virtual TexRotateTo* reverse() const override;
    
};


class CC_DLL TexScaleBy : public ActionInterval {
    
protected:
    float _startSX;
    float _startSY;
    float _deltaSX;
    float _deltaSY;
    
public:
    static TexScaleBy* create (float d, float deltaSX, float deltaSY);
    
    TexScaleBy ();
    virtual ~TexScaleBy ();
    
    bool initWithDuration (float d, float deltaSX, float deltaSY);
    
    virtual void startWithTarget (Node* pTarget) override;
    virtual void update (float time) override;
    
	virtual TexScaleBy* clone() const override;
    virtual TexScaleBy* reverse() const override;
    
};


class CC_DLL TexScaleTo : public TexScaleBy {
    
protected:
    float _targetSX;
    float _targetSY;
    
public:
    static TexScaleTo* create (float d, float sx, float sy);
    
    TexScaleTo ();
    virtual ~TexScaleTo ();
    
    bool initWithDuration (float d, float sx, float sy);
    
    virtual void startWithTarget (Node* pTarget) override;
    
	virtual TexScaleTo* clone() const override;
    virtual TexScaleTo* reverse() const override;
    
};


/**
 * degree
 */
class CC_DLL TexSkewBy : public ActionInterval {
    
protected:
    float _startKX;
    float _startKY;
    float _deltaKX;
    float _deltaKY;
    
public:
    static TexSkewBy* create (float d, float deltaKX, float deltaKY);
    
    TexSkewBy ();
    virtual ~TexSkewBy ();
    
    bool initWithDuration (float d, float deltaKX, float deltaKY);
    
    virtual void startWithTarget (Node* pTarget) override;
    virtual void update (float time) override;
    
	virtual TexSkewBy* clone() const override;
    virtual TexSkewBy* reverse() const override;
    
};


/**
 * degree
 */
class CC_DLL TexSkewTo : public TexSkewBy {
    
protected:
    float _targetKX;
    float _targetKY;
    
public:
    static TexSkewTo* create (float d, float kx, float ky);
    
    TexSkewTo ();
    virtual ~TexSkewTo ();
    
    bool initWithDuration (float d, float kx, float ky);
    
    virtual void startWithTarget (Node* pTarget) override;
    
	virtual TexSkewTo* clone() const override;
    virtual TexSkewTo* reverse() const override;
    
};


NS_CC_EXT_END

#endif /* defined(__CCTextureTransform__CCActionTextureTransform__) */
