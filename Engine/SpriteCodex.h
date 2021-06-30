#pragma once

#include "Graphics.h"
#include "Vec2.h"

class SpriteCodex
{
public:
	// centered drawing of 14x14 sprite
	static void DrawBall( const Vec2& center,Graphics& gfx );

	static void DrawTitle(const Vec2& centre, Graphics& gfx);

	static void SpriteCodex::DrawGameOver(const Vec2& centre, Graphics& gfx); 

	static void SpriteCodex::DrawReady(const Vec2& centre, Graphics& gfx);

	static void SpriteCodex::DrawPoo(const Vec2& centre, Graphics& gfx);
};