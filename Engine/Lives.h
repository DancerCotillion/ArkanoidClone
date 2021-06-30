#pragma once
#include "Graphics.h"
#include "SpriteCodex.h"
#include <algorithm>

class Lives
{
public:
	Lives(Vec2 pos_in, int lives_in)
		:
		pos (pos_in),
		lives(lives_in)
	{
	}

	bool ConsumeLive()
	{
		const bool hasLife = lives > 0;
		lives = std::max(lives - 1, 0);
		return hasLife;
	}

	void Draw(Graphics& gfx) const
	{
		const Vec2 offset(spacing, 0.0f);
		for (int c = 0; c < lives; c++)
		{
			SpriteCodex::DrawPoo(pos + offset * float(c), gfx); 
		}
	}

private:
	static constexpr float spacing = 28.0f; 
	Vec2 pos;
	int lives;
};