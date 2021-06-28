#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2& Pos_in, Vec2& Vel_in)
	:
	Pos ( Pos_in ),
	Vel ( Vel_in )
{
}

void Ball::update(float dt)
{
	Pos += Vel * dt; 
}

void Ball::Draw(Graphics& gfx)
{
	SpriteCodex::DrawBall(Pos, gfx);
}

bool Ball::doWallCollision(const Rectf& wall)
{
	const Rectf rect = GetRect();
	if (rect.left < wall.left)
	{
		Pos.x += wall.left - rect.left; 
		ReboundX();
		return true; 
	}
	else if (rect.right > wall.right)
	{
		Pos.x -= rect.right - wall.right; 
		ReboundX();
		return true; 
	}
	if (rect.top < wall.top)
	{
		Pos.y += wall.top - rect.top; 
		ReboundY();
		return true;
	}
	else if (rect.bottom > wall.bottom)
	{
		Pos.y -= rect.bottom - wall.bottom; 
		ReboundY();
		return true; 
	}
	return false;
}

void Ball::ReboundX()
{
	Vel.x = -Vel.x;
}

void Ball::ReboundY()
{	
	Vel.y = -Vel.y; 
}

Rectf Ball::GetRect()
{
	return Rectf::FromCentre(Pos, radius, radius);
}

Vec2 Ball::GetVelocity()
{
	return Vel;
}

Vec2 Ball::GetPos()
{
	return Pos;
}
