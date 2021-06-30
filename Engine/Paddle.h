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
	bool doBallCollision(Ball& ball); 
	void Update(Keyboard& kbd, float dt);

	Rectf GetRect() const; 

	void ResetCoolDown(); 

private:
	static constexpr Color c = Colors::White;
	static constexpr Color wingColor = Colors::Red;
	static constexpr float wingWidth = 6.0f;	
	static constexpr float speed = 360.0f;

	static constexpr float maximumExitRatio = 2.6f;
	static constexpr float fixedZoneWidthRatio = 0.2f;

	float halfWidth; 
	float halfHeight;

	float exitXFactor;
	float fixedZoneHalfWidth; 
	float fixedZoneExitX;

	bool isCoolDown = false;
	
	Vec2 pos;
};