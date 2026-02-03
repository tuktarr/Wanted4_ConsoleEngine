#include <iostream>
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/SokobanLevel.h"

using namespace Wanted;

int main()
{
	// 예시 배열
	const int width = 3;
	const int height = 3;
	CHAR_INFO charArray[width * height] = { };
	charArray[2 * 3 + 1].Char.AsciiChar = 'P';
	charArray[2 * 3 + 1].Attributes = FOREGROUND_GREEN;

	// 줄 나누는 건 누가 해주는 거?
	charArray[2 * 3 + 1].Char.AsciiChar = '#';
	charArray[2 * 3 + 1].Attributes = FOREGROUND_RED;

	COORD position = {};
	COORD screenSize;
	screenSize.X = width;
	screenSize.Y = height;

	SMALL_RECT writeRegion{
		0,
		0,
		static_cast<short>(width),
		static_cast<short>(height)
	};

	WriteConsoleOutputA(
		GetStdHandle(STD_OUTPUT_HANDLE),
		charArray,
		screenSize,
		position,
		&writeRegion
	);

	// CreateConsoleScreenBuffer() // flag만 잘 넣어주면됨
	// SetConsoleActiveScreenBuffer() -> 더블버퍼링할 것
	
	
	//Wanted::Engine engine;
	//engine.SetNewLevel(new SokobanLevel());
	//engine.Run();

	// 그래픽스에서 입력이 들어와 처리가 되면 최종 이미지를 만들 때, 화면에 나가는 이미지는
	// front 버퍼, 그래픽스에서 만드는 최종 이미지는s back 버퍼
	// 이미지 파일을 2장을 써서 픽셀값을 저장함. Back 버퍼와 Front 버퍼를 교환하면서 이미지가 바뀌는걸 보여줌
	// 그릴 때, 이미지 버퍼(Handle)를 한 개로 두고 콘솔 창을 2개로 둬서 콘솔 창을 바꿔치기할것
	
	// Actor (x,y)
	// Draw로 Rendering 함
	// char img actor
	// 기준 좌표계 왼쪽 대각선 위가 (0,0) 오른쪽으로 가면 +, 위로 가면 +

	//Game game;
	//game.Run();

	// 문자 배열을 한 번에 콘솔로 넘겨서 그릴 때 사용하는 함수
	std::cin.get();

}