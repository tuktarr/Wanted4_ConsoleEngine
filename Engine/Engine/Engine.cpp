#include "Engine.h"
#include "Level/Level.h"
#include <iostream>
#include <windows.h>

namespace Wanted
{
	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
		// 메인 레벨 제거.
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}
	}

	void Engine::Run()
	{
		// 시계의 정밀도
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		
		// 프레임 계산용 변수
		int64_t currentTime = 0;
		int64_t previousTime = 0;
		//__int64

		// 하드웨어 타이머로 시간 구하기
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);
		
		// 엔진 시작 직전에는 두 시간 값을 같게 맞춤 (방법 1 : 엄청 큰 값 무시, 방법 2 : 0값 무시)
		currentTime = time.QuadPart;
		previousTime = currentTime;

		// 기준 프레임 (단위 : 초)
		float targetFrameRate = 120.0f;
		float oneFrameTime = 1.0f / targetFrameRate;

		// 엔진 루프 (게임 루프)
		while(!isQuit)
		{
			// 현재 시간 구하기
			QueryPerformanceCounter(&time);
			currentTime = time.QuadPart;
			// timeGetTime(); // 시스템 시간을 밀리초 단위로 검색함. 1/1000초(가장 작은 단위의 시간 -> 1000프레임의 단위를 잴 수가 없다.)
			
			// 프레임 시간 계산.
			float deltaTime = static_cast<float>(currentTime - previousTime);
			
			// 초단위 변환
			deltaTime = deltaTime / static_cast<float>(frequency.QuadPart);
			
			// 고정 프레임 기법
			if (deltaTime >= oneFrameTime)
			{
				ProcessInput();

				// 프레임 처리
				BeginPlay();
				Tick(deltaTime);
				Draw();

				// 이전 시간 값 갱신
				previousTime = currentTime;

				// 현재 입력 값을 이전 입력 값으로 저장
				for (int ix = 0; ix < 255; ++ix)
				{
					keyStates[ix].wasKeyDown
						= keyStates[ix].isKeyDown;
				}
			}
		}

		// Todo: 정리 작업
		std::cout << "Engine has been shutdown...\n";
	}

	void Engine::QuitEngine()
	{
		isQuit = true;
	}

	bool Engine::GetKeyDown(int keyCode)
	{
		return keyStates[keyCode].isKeyDown && !keyStates[keyCode].wasKeyDown;
	}

	bool Engine::GetKeyUp(int keyCode)
	{
		return !keyStates[keyCode].isKeyDown && keyStates[keyCode].wasKeyDown;;
	}

	bool Engine::GetKey(int keyCode)
	{
		return keyStates[keyCode].isKeyDown;
	}

	void Engine::SetNewLevel(Level* newLevel)
	{
		// 기존 레벨 있는지 확인
		// 있으면 기존 레벨 제거
		// Todo: 임시 코드 레벨 전환할 때는 바로 제거하면 안됨
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}

		// 레벨 설정
		mainLevel = newLevel;

	}

	void Engine::ProcessInput()
	{
		// 키 마다의 입력 읽기
		// !!! 운영체제가 제공하는 기능을 사용할 수 밖에 없음.
		for (int ix = 0; ix < 255; ++ix)
		{
			keyStates[ix].isKeyDown = 
			GetAsyncKeyState(ix) & 0x8000 >0 ? true : false;
		}
	}

	void Engine::BeginPlay()
	{
		if (!mainLevel)
		{
			std::cout << "mainLevel is empty.\n";
			return;
		}

		mainLevel->BeginPlay();
	}

	void Engine::Tick(float deltaTime)
	{
		//std::cout 
		//	<< "DeltaTime : " << deltaTime
		//	<< ", FPS: " << (1.0f / deltaTime) << "\n";

		//// ESC키 눌리면 종료.
		if (GetKeyDown(VK_ESCAPE))
		{
			QuitEngine();
		}
	
		// 레벨에 이벤트 흘리기.
		// 예외처리
		if (!mainLevel)
		{
			std::cout << "Error: Engine::Tick(). mainLevel is empty\n";
			return;
		}

		mainLevel->Tick(deltaTime);
	}

	void Engine::Draw()
	{
		// 레벨에 이벤트 흘리기
		// 예외처리
		if (!mainLevel)
		{
			std::cout << "Error: Engine::Draw(). mainLevel is empty\n";
			return;
		}

		mainLevel->Draw();
	}
}