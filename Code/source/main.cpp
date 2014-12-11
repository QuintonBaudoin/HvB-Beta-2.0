#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#if !defined(OSX)
	#include <crtdbg.h>
#endif
#include <iostream>
#include <list>
#include <string>


#include "Decl.h"
#include "GameState.h"
#include "Assets.h"
#include "Player.h"
#include "ScoreBuffer.h"
#include "assetcreator(singleton).h"
#include "ScoreDatabase.h"
#include "sqlite3.h"


/*	
				Hotdog V. Burger
				14/10/2014
				Quinton Baudoin


			|------	 |^\	/^|	 |
			|		 |  \  /  |	 |
			|----	 |	 \/	  |	 |
			|		 |		  |	 |
			|		 |		  |	 |
			|ree	 |y		  |	 |______ife
*/






int g_State = eMenu;
int g_Last = eMenu;



int main(int argc, char* argv[])
{
	// Initialises screen and colors background
	///////////////////////////////////////////////////////
	Initialise(g_w, g_h, false, "HotDog v Burger");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));



	//activates Assets Singleton, Opens database, Creates game.
	//////////////////////////////////////////////////////
	Assets &ref = Assets::instance();
	ScoreDatabase::open();
	GameState myGame(20,&ref);
	//////////////////////////////////////////////////////
	

	bool is_e_key_down = false;
	bool is_q_key_down = false;
	
	do
	{
		ClearScreen();
		float dt = GetDeltaTime();

		

		switch (g_State)
		{


	//Main Menu: allows access to reccords, game, and exit:
////////////////////////////////////////////////////////////////////////////////////////////////////
		case eMenu:
				
			try { if (g_State != eMenu) throw "Illegal access to menu."; }
			catch (char *a){ std::cout << a << std::endl; system("pause") g_State = eClose; }

				if (!IsKeyDown('Q') && is_q_key_down){ g_State = ePlay; g_Last = g_State;  }
				is_q_key_down = IsKeyDown('Q');

				if (!IsKeyDown('E') && is_e_key_down){ g_State = eRecords;  }
				is_e_key_down = IsKeyDown('E');

				if (IsKeyDown('P')) { g_State = eClose;  };


				DrawString("Press  Q to start.", gv_gScreenLeft + 130, g_w / 2 - 20);
				DrawString("Press  E to see records.", gv_gScreenLeft + 130, g_w / 2 - 45);
				DrawString("Press  P close the  game.", gv_gScreenLeft + 130, g_w / 2 - 70);
				
				break;
	//Records: allows acces to previous state and close state
////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case eRecords:
			ScoreDatabase::draw();

			if (IsKeyDown('P')) { g_State = eClose;  }


			if (!IsKeyDown('E') && is_e_key_down) { g_State = g_Last;}
			is_e_key_down = IsKeyDown('E');
			
			break;


	//Game: allows acces to main menu close and records
/////////////////////////////////////////////////////////////////////////////////////////////
		case ePlay:

			

			if (!IsKeyDown('E') && is_e_key_down) g_State = eRecords;
			is_e_key_down = IsKeyDown('E');
			if (IsKeyDown('P')) g_State = eClose;




			if (!IsKeyDown('Q') && is_q_key_down){ g_State = eMenu; g_Last = g_State; }
			is_q_key_down = IsKeyDown('Q');


			myGame.Update(dt);
			myGame.Draw();
			
			break;						
		}
		
	} while (FrameworkUpdate()== false && g_State != eClose); //  == true


	

	
		//delete assets;

		ScoreDatabase::close();
	
	Shutdown();
	return 0;
}
