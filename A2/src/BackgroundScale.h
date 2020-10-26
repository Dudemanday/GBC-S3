#pragma once
#ifndef __BACKGROUND_SCALE__
#define __BACKGROUND_SCALE__
#include "DisplayObject.h"
class BackgroundScale :
    public DisplayObject
{
public:
	BackgroundScale();
	~BackgroundScale();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setPosition(glm::vec2 pos);

private:
	void m_reset();

};
#endif /* defined (__BACKGROUND_SCALE__) */
