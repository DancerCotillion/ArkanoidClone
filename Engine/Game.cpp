/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ball(Vec2(400.0f, 300.0f), Vec2(200.0f, 200.0f)),
	walls(0.0f, float(gfx.ScreenWidth), 0.0f, float(gfx.ScreenHeight)),
	paddle( Vec2(400.0f, 500.0f), 50.0f, 15.0f),
	WallBounce (L"Sounds\\arkpad.wav"),
	BrickBounce(L"Sounds\\arkbrick.wav")
{
	const Color ColorArray[4] = {Colors::Red, Colors::Green, Colors::Cyan, Colors::White};

	const Vec2 TopLeft(40.0f, 40.0f);

	int i = 0;
	for (int y = 0; y < nBricksRows; y++)
	{
		for (int x = 0; x < nBricksAcross; x++)
		{
			bricks[i] = Brick(Rectf(TopLeft+Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), ColorArray[y]);
			i++;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark(); 
	ball.update(dt);
	paddle.Update(wnd.kbd, dt);

	paddle.doWallCollision(walls);

	if (paddle.doBallCollision(ball))
	{
		WallBounce.Play(); 
	}

	for(Brick& b : bricks)
	{
		if (b.doCollision(ball))
		{
			BrickBounce.Play();
		}
	}
	if (ball.doWallCollision(walls))
	{
		WallBounce.Play(); 
	}

}

void Game::ComposeFrame()
{
	ball.Draw(gfx);
	paddle.Draw(gfx);

	for (const Brick& b : bricks)
	{
		b.Draw(gfx); 
	}
}
