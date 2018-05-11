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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	level(),
	place(0)
{

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
	auto input = wnd.kbd.ReadKey();
	
	if (input.IsPress())
	{
		place = input.GetCode(); 
		place -= '1';
		if (place >= 0 && place <= 5)
		{
			 mat = &samples[place];
		}
		if (std::toupper(input.GetCode()) == 'S')
		{
			level.Save("demoLevel.lvl");
		}
	}
	if (mat != nullptr)
	{
		if (!wnd.mouse.LeftIsPressed())
		{
			mat->SetPosition(Vec2_<int>(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()));
		}
		else
		{
			level.Add(*mat,place);
			mat = nullptr;
		}
	}

}

void Game::ComposeFrame()
{
	level.Draw(gfx);
	if (mat != nullptr)
	{
		mat->Draw(gfx);
	}
}
