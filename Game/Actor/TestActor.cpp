#include "TestActor.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include <iostream>
#include <Windows.h>

TestActor::TestActor()
	: super('T', Wanted::Vector2(2,3))
{

}

void TestActor::BeginPlay()
{
	// 상위 함수 호출.
	// C++는 부모함수 가리키는 포인터가 없음.
	Actor::BeginPlay();

	std::cout << "TestActor::BeginPlay().\n";
}

void TestActor::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// Q키 종료.
	if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		// Todo: 게임 엔진 종료 요청.
		Wanted::Engine::Get().QuitEngine();
	}
	
	// 이동
	if (Wanted::Input::Get().GetKey(VK_RIGHT) && GetPosition().x < 20)
	{
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.x += 1;
		SetPosition(newPosition);
	}
	
	if (Wanted::Input::Get().GetKey(VK_LEFT) && GetPosition().x > 0)
	{
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.x -= 1;
		SetPosition(newPosition);
	}

	//std::cout 
	//	<< "TestActor::Tick(). deltaTime: " << deltaTime
	//	<< ", FPS: " << (1.0f / deltaTime) << "\n";
}

void TestActor::Draw()
{
	Actor::Draw();
}
