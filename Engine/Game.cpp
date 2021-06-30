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
	//ball(Graphics::GetScreenRect().GetCentre(), Vec2(-0.5f, 1.0f)),
	walls(Rectf::FromCentre(Graphics::GetScreenRect().GetCentre(), fieldWidth / 2.0f, fieldHeight / 2.0f),
		wallThickness, wallColor),
	paddle( Vec2(400.0f, 500.0f), 50.0f, 15.0f),
	lifeCounter({30.0f, 30.0f}, 3),
	WallBounce (L"Sounds\\arkpad.wav"),
	BrickBounce(L"Sounds\\arkbrick.wav"),
	PlayFart(L"Sounds\\fart.wav"),
	Ready(L"Sounds\\Ready.wav")
{
	const Vec2 TopLeft(walls.getInnerBounds().left, walls.getInnerBounds().top + topSpace);
	int i = 0;
	for (int y = 0; y < nBricksRows; y++)
	{
		const Color c = ColorArray[y];

		for (int x = 0; x < nBricksAcross; x++)
		{
			bricks[i] = Brick(Rectf(
				TopLeft + Vec2(x * brickWidth, y * brickHeight),
				brickWidth, brickHeight), ColorArray[y]);
			i++;
		}
	}
	ResetBall();
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = ft.Mark(); 
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt; 
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	if (gameState == 1)
	{
		paddle.Update(wnd.kbd, dt);
		paddle.doWallCollision(walls.getInnerBounds());

		ball.update(dt);		

		if (paddle.doBallCollision(ball))
		{
			WallBounce.Play();
		}

		bool collisionHappened = false;
		float curColDistSq;
		int curColIndex;

		for (int i = 0; i < nBricks; ++i)
		{
			if (bricks[i].CheckBallCollision(ball))
			{
				const float newColDistSq = (ball.GetPos() - bricks[i].GetCentre()).GetLengthSq();
				if (collisionHappened)
				{
					if (newColDistSq < curColDistSq)
					{
						curColDistSq = newColDistSq;
						curColIndex = i;
					}
				}
				else
				{
					curColDistSq = newColDistSq;
					curColIndex = i;
					collisionHappened = true;
				}
			}
		}

		if (collisionHappened)
		{
			paddle.ResetCoolDown();
			bricks[curColIndex].doCollision(ball);
			BrickBounce.Play();
		}

		int wallCollisionTest = ball.doWallCollision(walls.getInnerBounds()); 

		if (wallCollisionTest == 1)
		{
			if (!paddle.GetRect().isOverlapping(ball.GetRect()))
			{
				paddle.ResetCoolDown();
			}		
			WallBounce.Play();
		}
		else if (wallCollisionTest == 2)
		{
			StartRound();
			ResetBall(); 
			PlayFart.Play(); 
		}
	}
	else if (gameState == 0)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			StartRound(); 
		}
	}
	else if (gameState == 3)
	{
		if ((curWaitTime += dt) > readyWaitTime)
		{
			gameState = 1; 
		}
	}

}

void Game::StartRound()
{
	if (lifeCounter.ConsumeLive())
	{
		curWaitTime = 0.0f;
		Ready.Play();
		gameState = 3;
	}
	else
	{
		gameState = 2; 
	}

}

void Game::ResetBall()
{
	//TODO: change this so it is at the position of the paddle. 
	ball = Ball(Graphics::GetScreenRect().GetCentre(), Vec2(-0.5f, 1.0f));
}

void Game::ComposeFrame()
{
	if (gameState == 1 || gameState == 3)
	{
		paddle.Draw(gfx);
		lifeCounter.Draw(gfx); 
	}
	if (gameState == 3)
	{
		SpriteCodex::DrawReady(Graphics::GetScreenRect().GetCentre(), gfx);
	}
	if (gameState == 1)
	{
		ball.Draw(gfx);
	}
	if (gameState != 0)
	{
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
		walls.Draw(gfx);
	}
	if (gameState == 0)
	{
		SpriteCodex::DrawTitle(Graphics::GetScreenRect().GetCentre(), gfx); 
	}
	else if (gameState == 2)
	{
		SpriteCodex::DrawGameOver(Graphics::GetScreenRect().GetCentre(), gfx);
	}
}
