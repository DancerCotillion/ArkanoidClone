#include "Rectf.h"

Rectf::Rectf(float left_in, float right_in, float top_in, float bottom_in)
	:
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
{
}

Rectf::Rectf(const Vec2& topLeft, const Vec2& bottomRight)
	:
	Rectf(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

Rectf::Rectf(const Vec2& topLeft, float width, float height)
	:
	Rectf(topLeft, topLeft + Vec2(width, height))
{
}

bool Rectf::isOverlapping(const Rectf& other) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}

bool Rectf::isContainedBy(const Rectf& other)
{
	return left >=other.left && right <=other.right &&
		top >= other.top && bottom <= other.bottom;
}

Rectf Rectf::GetExpanded(float offset) const
{
	return Rectf(left - offset, right + offset, top - offset, bottom + offset);
}

Vec2 Rectf::GetCentre() const
{
	return Vec2( (left + right) / 2.0f, (top + bottom) /2.0f);
}

Rectf Rectf::FromCentre(const Vec2& centre, float halfWidth, float halfHeight)
{
	const Vec2 half(halfWidth, halfHeight);
	return Rectf(centre - half, centre + half);
}