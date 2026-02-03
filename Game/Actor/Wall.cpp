#include "Wall.h"

Wall::Wall(const Vector2& position)
	: super("#", position, Color::White)
{
	// 그리기 우선순위 설정
	sortingOrder = 0; // 벽은 다른 물체랑 겹쳐지지않는다. 우선순위가 필요없다

}
