#include "Level.h"
#include "Actor/Actor.h"

namespace Wanted
{
	Level::Level()
	{

	}

	Level::~Level()
	{
		// 메모리 정리.
		for (Actor*& actor : actors)
		{
			if (actor)
			{
				delete actor;
				actor = nullptr;
			}
		}

		// 배열 초기화
		actors.clear();
	}

	void Level::BeginPlay()
	{
		for (Actor* actor : actors)
		{
			// 이미 BeginPlay 호출된 액터는 건너뛰기
			if (actor->HasBeganPlay())
			{
				continue;
			}

			actor->BeginPlay();
		}
	}

	void Level::Tick(float deltaTime)
	{
		for (Actor* actor : actors)
		{
			// 엑터에 이벤트 흘리기
			actor->Tick(deltaTime);
		}
	}

	void Level::Draw()
	{
		for (Actor* actor : actors)
		{
			// 엑터에 이벤트 흘리기
			actor->Draw();
		}
	}
	void Level::AddNewActor(Actor* newActor)
	{
		// Todo: 나중에 프레임 처리 고려해서 따로 추가 작업 해야함
		//actors.push_back(newActor);
		actors.emplace_back(newActor);

		// emplace와 아닌 함수의 차이점?
		// push류 함수는 LvalueRef를 받음 -> 데이터 복사를 함
		// emplace는 RvalueRef를 받음 -> 복사를 안함(주소값만 복사함)
		// 요즘은 둘 다 RvalueRef를 받음, 하지만 Push류가 LValueRef를 받을 수도 있음.
		// 기본적으로 Emplace를 쓰는것이 RvalueRef를 우선순위로 받음
	}
}