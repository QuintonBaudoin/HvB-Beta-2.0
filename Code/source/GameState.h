#pragma once
#include "Decl.h"

#include<vector>
#include <queue>
/*Declares gamestate variabls and functions*/
class GameState
{
	Player *m_player;
	Player *m_hotdog;

	std::vector<Bullet*> m_bullets;
	std::queue<Bullet*> myQueue;
	int score_1, score_2, win_1, win_2, score_d;
	char text[32];

	int nBullets;		   
	Assets *e_assets;	   
	int m_padding;		

public:

	GameState(int a_padding, Assets *a_assets);
	~GameState();

	int GetPadding();

	void SpawnBullet(int a_x, int a_y, float a_speed, unsigned a_shot);
	


	void Update(float a_dt);
	void Draw();

};