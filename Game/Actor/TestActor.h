#pragma once

#include "Actor/Actor.h"

// test -> Actor -> RTTI
class TestActor : public Wanted::Actor
{
	RTTI_DECLARATIONS(TestActor, Actor)

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};
