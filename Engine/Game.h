/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Rectf.h"
#include "Ball.h"
#include "FrameTimer.h"
#include "Sound.h"
#include "Brick.h"
#include "Paddle.h"
#include "Walls.h"
#include "SpriteCodex.h"
#include "Lives.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	void StartRound(); 
	void ResetBall(); 
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	
	
	static constexpr float brickWidth = 40.0f;
	static constexpr float brickHeight = 22.0f;
	static constexpr float topSpace = brickHeight * 1.6f;
	static constexpr int nBricksRows = 4;
	static constexpr int nBricksAcross = 12;
	static constexpr int nBricks = nBricksRows * nBricksAcross;

	static constexpr Color ColorArray[4] = { {230,0,0},{ 0,230,0 },{ 0,0,230 },{ 0,230,230 } };

	Brick bricks[nBricks]; 

	int gameState = 0; 
	static constexpr float readyWaitTime = 4.3f;
	float curWaitTime; 

	FrameTimer ft; 
	Ball ball; 
	Paddle paddle; 
	Sound WallBounce;
	Sound BrickBounce; 
	Sound PlayFart; 
	Sound Ready;

	Walls walls; 
	
	Lives lifeCounter; 

	static constexpr float wallThickness = 12.0f;
	static constexpr float fieldWidth = float(nBricksAcross) * brickWidth;
	static constexpr float fieldHeight = float(Graphics::ScreenHeight) - wallThickness * 2.0f;
	static constexpr Color wallColor = { 20,60,200 };

	bool gameIsOver = false;
	/********************************/
};