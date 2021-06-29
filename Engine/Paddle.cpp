#include "Paddle.h"
#include <cmath>

Paddle::Paddle(const Vec2& pos_in, float width_in, float height_in)
	:
	pos (pos_in),
	halfWidth (width_in),
	halfHeight (height_in)
{
}

void Paddle::Draw(Graphics& gfx)
{
	Rectf rect = GetRect();
	gfx.DrawRect(rect, c);
	rect.left += wingWidth;
	rect.right -= wingWidth; 
	gfx.DrawRect(rect, wingColor); 
}

void Paddle::doWallCollision(const Rectf& walls)
{
	Rectf rect = GetRect(); 
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right; 
	}
}

bool Paddle::doBallCollision(Ball& ball)
{
	if (!isCoolDown)
	{
		const Rectf rect = GetRect();
		if (rect.isOverlapping(ball.GetRect()))
		{
			const Vec2 ballPos = ball.GetPos();

			if (std::signbit(ball.GetVelocity().x) == std::signbit((ballPos - pos).x)
				|| (ballPos.x >= rect.left && ballPos.x <= rect.right))
			{
				Vec2 dir; 
				const float xDifference = ballPos.x - pos.x;
				const float fixedXComponent = fixedZoneHalfWidth * exitXFactor; 
				if (std::abs(xDifference) < fixedZoneHalfWidth)
				{
					if (xDifference < 0.0f)
					{
						dir = Vec2(-fixedXComponent, -1.0f);
					}
					else
					{
						dir = Vec2(fixedXComponent, -1.0f);
					}
				}
				else
				{
					dir = Vec2(xDifference * exitXFactor, -1.0f); 
				}
				ball.SetDirection(dir); 
			}
			else
			{
				ball.ReboundX();
			}
			isCoolDown = true; 
			return true;
		}
	}
	return false; 
}

void Paddle::Update(Keyboard& kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * dt; 
	}
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
}

Rectf Paddle::GetRect() const
{
	 return Rectf::FromCentre(pos, halfWidth, halfHeight);
}

void Paddle::ResetCoolDown()
{
	isCoolDown = false;
}


