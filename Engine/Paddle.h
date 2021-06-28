#pragma once
#include "Colors.h"
#include "Vec2.h"
#include "Graphics.h"
#include "Ball.h"
#include "Keyboard.h"
#include "Rectf.h"

class Paddle
{
public:
	Paddle(const Vec2& pos_in, float width_in, float height_in); 
	void Draw(Graphics& gfx);
	void doWallCollision(const Rectf& walls);
	bool doBallCollision(Ball& ball) const; 
	void Update(Keyboard& kbd, float dt);

	Rectf GetRect() const; 

private:
	Color c = Colors::White;
	Vec2 pos;
	static constexpr float wingWidth = 15;
	static constexpr Color wingColor = Colors::Red;
	float halfWidth; 
	float halfHeight;
	float speed = 300.0f; 
};