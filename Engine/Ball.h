#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Rectf.h"

class Ball
{
public:
	Ball() = default;
	Ball(const Vec2& Pos_in, Vec2& Dir_in);
	void update(float dt);
	void Draw(Graphics& gfx);

	// return 0 = no collision, 1 = wall collision, 2 = hit the bottom (GAME OVER)
	int doWallCollision(const Rectf& wall);

	void ReboundX();
	void ReboundY(); 

	Rectf GetRect() const;
	Vec2 GetVelocity();
	Vec2 GetPos();

	void SetDirection(const Vec2& dir); 

private:
	Vec2 Pos;
	Vec2 Vel;
	float speed = 400.0f; 
	static constexpr float radius = 7;
};


