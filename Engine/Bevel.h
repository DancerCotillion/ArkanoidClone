#pragma once
#include "Colors.h"
#include "Rectf.h"
#include "Graphics.h"

class Bevel
{
public:
	Bevel() = default; 
	Bevel(Color baseColor);
	void DrawOuterBevel(const Rectf& rect, int size, Graphics& gfx) const;
	void DrawInnerBevel(const Rectf& rect, int size, Graphics& gfx) const;
	void DrawBeveledBrick(const Rectf& rect, int bevelSize, Graphics& gfx) const; 
	void DrawBeveledFrame(const Rectf& rect, int bevelSize, Graphics& gfx) const;
	Color GetBaseColor() const; 
	void setBaseColor(Color base_in); 

private:
	static constexpr float leftFactor = 1.10f;
	static constexpr float topFactor = 0.93f;
	static constexpr float bottomFactor = 0.80f; 
	static constexpr float rightFactor = 0.65f;

	Color baseColor;
	Color topColor;
	Color bottomColor;
	Color leftColor; 
	Color rightColor; 
};