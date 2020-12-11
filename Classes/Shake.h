#ifndef __SHAKE_H__
#define __SHAKE_H__

#include "cocos2d.h"

USING_NS_CC;

// Code by Francois Guibert
// Contact: www.frozax.com - http://twitter.com/frozax - www.facebook.com/frozax
class CC_DLL Shake : public ActionInterval
{
private:


public:
	Shake();

	// Create the action with a time and a strength (same in x and y)
	static Shake* actionWithDuration(float d, float strength );

	// Create the action with a time and strengths (different in x and y)
	static Shake* actionWithDuration(float d, float strength_x, float strength_y );

	bool initWithDuration(float d, float strength_x, float strength_y );

	virtual void startWithTarget(Node *pTarget);
	virtual void update(float time);
	virtual void stop(void);

	virtual Shake* reverse() const;
	virtual Shake* clone() const;

protected:
	float _initial_x, _initial_y;
	float _strength_x, _strength_y;
	float _duration;
};

#endif //__SHAKE_H__