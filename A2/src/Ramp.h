#pragma once
#ifndef __RAMP__
#define __RAMP__

#include "DisplayObject.h"
class Ramp : public DisplayObject
{
public:
	Ramp();
	~Ramp();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setPosition(glm::vec2 pos);

private:
	void m_reset();

};


#endif /* defined (__RAMP__) */