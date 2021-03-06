#include "Ball.h"
#include "Brick.h"
#include <assert.h>
#include <cmath>

Brick::Brick(Rectf& rect_in, Color c_in)
	:
	Rect(rect_in),
	c(c_in)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if (!Destroyed)
	{
		gfx.DrawRect(Rect.GetExpanded(-padding), c);
	}	
}

bool Brick::CheckBallCollision(const Ball& ball) const
{
	return !Destroyed && Rect.isOverlapping(ball.GetRect());
}


void Brick::doCollision(Ball& ball)
{
	assert(CheckBallCollision(ball));
	const Vec2 ballPos = ball.GetPos(); 

	if (std::signbit(ball.GetVelocity().x) == std::signbit((ballPos - GetCentre()).x))
	{
		ball.ReboundY();
	}

	else if (ballPos.x >= Rect.left && ballPos.x <= Rect.right)
	{
		ball.ReboundY();
	}
	else
	{
		ball.ReboundX();
	}
	Destroyed = true;
}

Vec2 Brick::GetCentre() const
{
	return Rect.GetCentre();
}
