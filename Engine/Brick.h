#pragma once
#include "Rectf.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"
#include "Bevel.h"

class Brick
{
public: 
	Brick() = default; 
	Brick(Rectf& rect_in, Color c_in);
	void Draw(Graphics& gfx) const;
	bool CheckBallCollision(const Ball& ball) const; 
	void doCollision(Ball& ball); 

	Vec2 GetCentre() const;

private:
	static constexpr float padding = 0.5f; 
	static constexpr int bevelSize = 3;
	Bevel bev;
	Rectf Rect; 
	bool Destroyed = false; 
};