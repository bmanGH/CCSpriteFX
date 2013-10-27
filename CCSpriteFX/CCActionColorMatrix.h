//
//  CCActionColorMatrix.h
//  CCSpriteFX
//
//  Created by bman on 7/24/13.
//
//

#ifndef __SZSG__CCActionColorMatrix__
#define __SZSG__CCActionColorMatrix__

#include "cocos2d.h"
#include "CCColorMatrix.h"

USING_NS_CC;

NS_CC_EXT_BEGIN


// base color matrix action
class CC_DLL ColorMatrixActionInterval : public ActionInterval {
protected:
    bool _needConcat;
    
protected:
    ColorMatrixActionInterval ();
    virtual ~ColorMatrixActionInterval ();
    bool initWithDuration (float d, bool needConcat);
    void updateTargetColorMatrix (ColorMatrix4x4& cmat);
    
public:
    virtual void startWithTarget (Node *pTarget);
    virtual void update (float time) override = 0;
    
	virtual ColorMatrixActionInterval* clone() const override = 0;
    virtual ColorMatrixActionInterval* reverse() const override = 0;
};

class CC_DLL ColorMatrixActionInstant : public ActionInstant {
protected:
    bool _needConcat;
    
protected:
    ColorMatrixActionInstant ();
    virtual ~ColorMatrixActionInstant ();
    bool init (bool needConcat);
    void updateTargetColorMatrix (ColorMatrix4x4& cmat);
    
public:
    virtual void startWithTarget (Node *pTarget);
    virtual void update (float time) override = 0;
    
	virtual ColorMatrixActionInstant* clone() const override = 0;
    virtual ColorMatrixActionInstant* reverse() const override = 0;
};


// color scale
class CC_DLL ColorMatrixScale : public ColorMatrixActionInterval {
protected:
    float _fromR, _toR;
    float _fromG, _toG;
    float _fromB, _toB;
    
public:
    /**
     * @param 0~1
     */
    static ColorMatrixScale* create (float d, float fromR, float toR, float fromG, float toG, float fromB, float toB, bool needConcat = false);
    
    ColorMatrixScale ();
    virtual ~ColorMatrixScale ();
    /**
     * @param 0~1
     */
    bool initWithDuration (float d, float fromR, float toR, float fromG, float toG, float fromB, float toB, bool needConcat = false);
    
    virtual void update (float time) override;
    
	virtual ColorMatrixScale* clone() const override;
    virtual ColorMatrixScale* reverse() const override;
};


// color offset
class CC_DLL ColorMatrixOffset : public ColorMatrixActionInterval {
protected:
    float _fromR, _toR;
    float _fromG, _toG;
    float _fromB, _toB;
    
public:
    /**
     * @param -1~1
     */
    static ColorMatrixOffset* create (float d, float fromR, float toR, float fromG, float toG, float fromB, float toB, bool needConcat = false);
    
    ColorMatrixOffset ();
    virtual ~ColorMatrixOffset ();
    /**
     * @param -1~1
     */
    bool initWithDuration (float d, float fromR, float toR, float fromG, float toG, float fromB, float toB, bool needConcat = false);
    
    virtual void update (float time) override;
    
	virtual ColorMatrixOffset* clone() const override;
    virtual ColorMatrixOffset* reverse() const override;
};


// brightness
class CC_DLL ColorMatrixBrightness : public ColorMatrixActionInterval {
protected:
    float _from;
    float _to;
    
public:
    /**
     * @param -1~1
     */
    static ColorMatrixBrightness* create (float d, float from, float to, bool needConcat = false);
    
    ColorMatrixBrightness ();
    virtual ~ColorMatrixBrightness ();
    /**
     * @param -1~1
     */
    bool initWithDuration (float d, float from, float to, bool needConcat = false);
    
    virtual void update (float time) override;
    
	virtual ColorMatrixBrightness* clone() const override;
    virtual ColorMatrixBrightness* reverse() const override;
};


// saturation
class CC_DLL ColorMatrixSaturation : public ColorMatrixActionInterval {
    float _from;
    float _to;
    
public:
    /**
     * @param 0~1
     */
    static ColorMatrixSaturation* create (float d, float from, float to, bool needConcat = false);
    
    ColorMatrixSaturation ();
    virtual ~ColorMatrixSaturation ();
    /**
     * @param 0~1
     */
    bool initWithDuration (float d, float from, float to, bool needConcat = false);
    
    virtual void update (float time) override;
    
	virtual ColorMatrixSaturation* clone() const override;
    virtual ColorMatrixSaturation* reverse() const override;
};


// contrast
class CC_DLL ColorMatrixContrast : public ColorMatrixActionInterval {
    float _from;
    float _to;
    
public:
    /**
     * @param 0~1
     */
    static ColorMatrixContrast* create (float d, float from, float to, bool needConcat = false);
    
    ColorMatrixContrast ();
    virtual ~ColorMatrixContrast ();
    /**
     * @param 0~1
     */
    bool initWithDuration (float d, float from, float to, bool needConcat = false);
    
    virtual void update (float time) override;
    
	virtual ColorMatrixContrast* clone() const override;
    virtual ColorMatrixContrast* reverse() const override;
};


// threshold
class CC_DLL ColorMatrixThreshold : public ColorMatrixActionInterval {
    float _from;
    float _to;
    
public:
    /**
     * @param -1~1
     */
    static ColorMatrixThreshold* create (float d, float from, float to, bool needConcat = false);
    
    ColorMatrixThreshold ();
    virtual ~ColorMatrixThreshold ();
    /**
     * @param -1~1
     */
    bool initWithDuration (float d, float from, float to, bool needConcat = false);
    
    virtual void update (float time) override;
    
	virtual ColorMatrixThreshold* clone() const override;
    virtual ColorMatrixThreshold* reverse() const override;
};


// HUE
class CC_DLL ColorMatrixHUE : public ColorMatrixActionInterval {
    float _from;
    float _to;
    
public:
    /**
     * @param -1~1
     */
    static ColorMatrixHUE* create (float d, float from, float to, bool needConcat = false);
    
    ColorMatrixHUE ();
    virtual ~ColorMatrixHUE ();
    /**
     * @param -1~1
     */
    bool initWithDuration (float d, float from, float to, bool needConcat = false);
    
    virtual void update (float time) override;
    
	virtual ColorMatrixHUE* clone() const override;
    virtual ColorMatrixHUE* reverse() const override;
};


// Identity / Inversion

class CC_DLL ColorMatrixIdentity : public ColorMatrixActionInstant {
public:
    static ColorMatrixIdentity* create (bool needConcat = false);
    
    ColorMatrixIdentity ();
    virtual ~ColorMatrixIdentity ();
    bool init (bool needConcat = false);

    virtual void update (float time) override;
    
	virtual ColorMatrixIdentity* clone() const override;
    virtual ColorMatrixActionInstant* reverse() const override;
};

class CC_DLL ColorMatrixInversion : public ColorMatrixActionInstant {
public:
    static ColorMatrixInversion* create (bool needConcat = false);
    
    ColorMatrixInversion ();
    virtual ~ColorMatrixInversion ();
    bool init (bool needConcat = false);
    
    virtual void update (float time) override;
    
	virtual ColorMatrixInversion* clone() const override;
    virtual ColorMatrixActionInstant* reverse() const override;
};


// enable / disable need reset color matrix after draw action

class CC_DLL ColorMatrixSetNeedResetColorMatrix : public ActionInstant {
protected:
    bool _needResetColorMatrix;
    
public:
    static ColorMatrixSetNeedResetColorMatrix* create (bool needResetColorMatrix);
    
    ColorMatrixSetNeedResetColorMatrix ();
    virtual ~ColorMatrixSetNeedResetColorMatrix ();
    bool init (bool needResetColorMatrix);
    
    virtual void startWithTarget (Node *pTarget);
    virtual void update (float time) override;
    
	virtual ColorMatrixSetNeedResetColorMatrix* clone() const override;
    virtual ColorMatrixSetNeedResetColorMatrix* reverse() const override;
};


NS_CC_EXT_END

#endif /* defined(__SZSG__CCActionColorMatrix__) */
