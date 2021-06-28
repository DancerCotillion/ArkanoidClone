#include "Paddle.h"

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

bool Paddle::doBallCollision(Ball& ball) const
{
	if (ball.GetVelocity().y > 0.0f && GetRect().isOverlapping(ball.GetRect()))
	{
		ball.ReboundY();
		return true; 
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


