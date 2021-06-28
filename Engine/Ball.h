#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Rectf.h"

class Ball
{
public:
	Ball(const Vec2& Pos_in, Vec2& Vel_in);
	void update(float dt);
	void Draw(Graphics& gfx);

	bool doWallCollision(const Rectf& wall);

	void ReboundX();
	void ReboundY(); 

	Rectf GetRect();

	Vec2 GetVelocity();

private:
	Vec2 Pos;
	Vec2 Vel;
	static constexpr float radius = 7;
};


