#pragma once
#include "Vec2.h"

class Rectf
{
public:
	Rectf() = default;
	Rectf(float left_in, float right_in, float top_in, float bottom_in);
	Rectf(const Vec2& TopLeft, const Vec2& BottomRight);
	Rectf(const Vec2& TopLeft, float width, float height);

	static Rectf FromCentre(const Vec2& centre, float halfWidth, float halfHeight);

	bool isOverlapping(const Rectf& other) const;

	Rectf GetExpanded(float offset) const;
	Vec2 GetCentre() const; 

public:
	float left;
	float right;
	float top;
	float bottom;
};