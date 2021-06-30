#pragma once
#include "Colors.h"
#include "Rectf.h"
#include "Graphics.h"
#include "Bevel.h"

class Walls
{
public:
	Walls(const Rectf& innerBounds_in, float thickness_in, Color baseColor);

	const Rectf& getInnerBounds() const; 
	void Draw(Graphics& gfx) const;

private:
	Rectf innerBounds;
	float thickness;
	Bevel bev; 

};