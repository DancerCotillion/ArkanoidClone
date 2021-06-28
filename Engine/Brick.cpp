#include "Ball.h"
#include "Brick.h"

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

bool Brick::doCollision(Ball& ball)
{
	if (!Destroyed && Rect.isOverlapping(ball.GetRect()))
	{
		if (ball.GetPos().x >= Rect.left && ball.GetPos().x <= Rect.right)
		{
			ball.ReboundY();
		}
		else
		{
			ball.ReboundX(); 
		}		
		Destroyed = true; 
		return true; 
	}
	return false;
}
