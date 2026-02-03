#pragma once

#include "Math/Vector2.h"
#include <Windows.h>

namespace Wanted
{
	/*
	* 작성자: 장세윤
	* 날짜 : 2026.02.03
	* 내용더블 버퍼링에 사용할 Console Output 핸들을 관리하는 클래스
	*/

	// 버퍼라는걸 뭐라고 생각하면 될까?
	class ScreenBuffer
	{
	public:
		ScreenBuffer(const Vector2& screenSize);
		~ScreenBuffer();

		// 콘솔 버퍼를 지우는 함수
		void Clear();

		// 콘솔에 2차원 글자 배열을 그릴 때, 사용하는 함수
		// CHAR_INFO 뭐냐?
		void Draw(CHAR_INFO* charInfo);

		// 버퍼 반환 Getter
		inline HANDLE GetBuffer() const { return buffer; }

	private:
		// void* : 주소값, nullptr로 초기화 가능
		// 콘솔 출력 핸들
		HANDLE buffer = nullptr;
		
		// 화면 크기
		Vector2 screenSize;

	};
}


