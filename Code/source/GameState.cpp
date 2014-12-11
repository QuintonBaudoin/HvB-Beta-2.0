#include "GameState.h"
#include "Player.h"
#include "Assets.h"
#include "Bullet.h"

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "ScoreDatabase.h"
using namespace std;;

int GameState::GetPadding() { return m_padding; }

/*

	Manages how the game runs.

*/

/*
		Starts game by creating 2 players and bullet array
*/



// Sets all the start up scores and players
GameState::GameState(int a_padding, Assets *a_assets)
{
	/////Scores//////////////////////////
	score_1 = 0;
	score_2 = 0;
	win_1 = 0;
	win_2 = 0;
	///Players///////////////////////////
	m_padding = a_padding;
	e_assets  = a_assets;

	m_player = new Player(this, e_assets->Get(ePlayer), 80, 80, 150, .25f, 'I', 'K', 'J', 'L', ';', gv_gScreenMid, gv_gScreenRight, ePickle);

	m_hotdog = new Player(this, e_assets->Get(eHotDog), 80, 80, 150, .25f, 'W', 'S', 'A', 'D', 'F', gv_gScreenLeft, gv_gScreenMid,  eTot);



}


/*
	Updates game

*/



void GameState::Update(float a_dt)
{
	

	/*If players exists it uses the Update Player functions*/
	if (m_player || m_hotdog)
	{
		m_player->Update(a_dt);
		m_hotdog->Update(a_dt);
	}

	
	/* Manages bullets */
	//for (int i = 0; i < 2 ; ++i)
	//{
		/*If bullets exist updates them using Bullet update functions*/
		auto it = m_bullets.begin();
		while (it != m_bullets.end())
		{
			if ((*it)->IsActive())
			{
				(*it)->Update(a_dt);
				
				////////////////////////////Checks for collision using Collides(m_player) if collides point goes to Hotdog
				if ((*it)->Collides(m_player))
				{
					delete *it;
					it = m_bullets.erase(it);
					if (score_1 < 10)score_1++;
					else
					{
						score_d = (score_1 - score_2);
						score_1 = 0; score_2 = 0; win_1++;
						ScoreDatabase::addScore("HotDog won ", score_d);
					 }
				}
				////////////////////////////Checks for collision using Collides(m_player) if collides point goes to Burger
				else if ((*it)->Collides(m_hotdog))
				{
					delete *it;
					it = m_bullets.erase(it);					
					if (score_2 < 10)score_2++;
					else
					{
						score_d = (score_2 - score_1);
						score_1 = 0; score_2 = 0; win_2++;
						ScoreDatabase::addScore("Burger won ", score_d);
					}
				}
				else it++; // If it's active and didn't collide, increment iterator
				}
			else it++; // if it's inactive, we still need to increment the iterator
			}
		////Moves Bullets from Queue to the vector
		while (!myQueue.empty())
		{
			m_bullets.push_back(myQueue.front());
			myQueue.pop();
		}
		}

		

	
	/* calls for Draws functions for the sprites and draws the scores at the bottom of the screan*/

void GameState::Draw()
{	//Scoring draw.

	const unsigned int Background = CreateSprite("./images/Back.jpg", g_w, g_h, true);
	MoveSprite(Background,g_w / 2,g_h / 2);
	DrawSprite(Background);
	

	{
		char output[16] = "Score: ";	
		char c_score[8];				
		itoa(score_1, c_score, 10);     
		strcat_s(output, 16, c_score);	
		DrawString(output, 50, 50);		
	}
	{
		char output[16] = "Score: ";	
		char c_score[8];				
		itoa(score_2, c_score, 10);     
		strcat_s(output, 16, c_score);	
		DrawString(output, 840, 50);		
	}
	// Winnings draw
	{
			char output[16] = "Wins ";	
			char c_score[8];				
			itoa(win_1, c_score, 10);   
			strcat_s(output, 16, c_score);	
			DrawString(output, 50, 100);	 
	}

	{
			char output[16] = "Wins ";		
			char c_score[8];				
			itoa(win_2, c_score, 10);		
			strcat_s(output, 16, c_score);		
			DrawString(output, 840, 100);		
	}

	

	/*Draws players if they exist*/
	if (m_player || m_hotdog){ m_player->Draw();  m_hotdog->Draw(); }

	
		/*Draws Bullets if they exist*/

	auto it = m_bullets.begin();
	while (it != m_bullets.end())
	{
		if ((*it)->IsActive()) (*it)->Draw();
		it++;
	}
}

void GameState::SpawnBullet(int a_x, int a_y, float a_speed, unsigned a_shot)
{
	////// Adds bullets to the queue based of of witch player shot using eTot and ePickle as the switch

		switch (a_shot)
		{
			case eTot:
					myQueue.push(new Bullet(this, e_assets->Get(eTot), a_x, a_y, 10, 14, a_speed));
					return;

			case ePickle:
					myQueue.push(new Bullet(this, e_assets->Get(ePickle), a_x, a_y, 10, 14, a_speed));
					return;
		}
		
}

GameState::~GameState()
{
	delete m_player;
	delete m_hotdog;
}