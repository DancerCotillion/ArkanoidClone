#pragma once
#include "Rectf.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
public: 
	Brick() = default; 
	Brick(Rectf& rect_in, Color c_in);
	void Draw(Graphics& gfx) const;
	bool CheckBallCollision(const Ball& ball) const; 
	bool doCollision(Ball& ball); 

private:
	static constexpr float padding = 1.0f; 
	Rectf Rect; 
	Color c;
	bool Destroyed = false; 
};