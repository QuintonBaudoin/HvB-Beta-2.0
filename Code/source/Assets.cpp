#include "Assets.h"


Assets::Assets()
{	
	
	// sets array to nullptr
	for (int i = 0; i < g_maxSprites; ++i)
	{
		sprites[i] = nullptr;
		if (i < eSize) assoc[i] = nullptr;
	}

	nSprites = 0;

	LoadSprite("./images/burgervan.png", 80, 80, ePlayer);
	LoadSprite("./images/PickleBullets.png", 40, 40, ePickle);
	LoadSprite("./images/Tot.png", 40, 40, eTot);
	LoadSprite("./images/Back.jpg", 1000, 70, eBack);
	LoadSprite("./images/hotdogtruck.png", 80, 80, eHotDog);	
}


unsigned Assets::Get(eSpriteFlag s) { return *assoc[s]; }

/*Loads sprites using the variables "path" for the path name of the loaded texture, W/h is the Width/Hight of the sprite, What action the sprite has, and weither the sprite loads center screen or not.*/

unsigned Assets::LoadSprite(char *path, int w, int h, eSpriteFlag s, bool center)
{
	if (nSprites < 64)
	{
		unsigned *t = new unsigned(CreateSprite(path, w, h, center));

		sprites[nSprites++] = t; 
		if (s != eNone)
			assoc[s] = t;			

		return *t;
	}
	return 0;
}
/*Destructor for sprites*/
Assets::~Assets()
{
	for (int i = 0; i < g_maxSprites; ++i)
		if (sprites[i])
		{
			DestroySprite(*sprites[i]);
								

			delete sprites[i];
		}
}