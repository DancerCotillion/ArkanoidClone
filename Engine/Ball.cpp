#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2& Pos_in, Vec2& Dir_in)
	:
	Pos ( Pos_in )
{
	SetDirection(Dir_in); 
}

void Ball::update(float dt)
{
	Pos += Vel * dt; 
}

void Ball::Draw(Graphics& gfx)
{
	SpriteCodex::DrawBall(Pos, gfx);
}

int Ball::doWallCollision(const Rectf& wall)
{
	const Rectf rect = GetRect();
	if (rect.left < wall.left)
	{
		Pos.x += wall.left - rect.left; 
		ReboundX();
		return 1; 
	}
	else if (rect.right > wall.right)
	{
		Pos.x -= rect.right - wall.right; 
		ReboundX();
		return 1; 
	}
	if (rect.top < wall.top)
	{
		Pos.y += wall.top - rect.top; 
		ReboundY();
		return 1;
	}
	else if (rect.bottom > wall.bottom)
	{
		Pos.y -= rect.bottom - wall.bottom; 
		ReboundY();
		return 2; 
	}
	return 0;
}

void Ball::ReboundX()
{
	Vel.x = -Vel.x;
}

void Ball::ReboundY()
{	
	Vel.y = -Vel.y; 
}

Rectf Ball::GetRect() const
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

void Ball::SetDirection(const Vec2& dir)
{
	Vel = dir.GetNormalized() * speed; 
}
