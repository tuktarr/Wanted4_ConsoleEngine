#pragma once

#include "Common/Common.h"
#include "Actor.h"
class WANTED_API TestActor : public Wanted::Actor
{
protected:
	virtual void Beginplay();
	virtual void Tick(float deltaTime);
	virtual void Draw();
};

