#pragma once
#include "Decl.h"

/*declares assets*/
class Assets
{
	unsigned *sprites[g_maxSprites];
	unsigned *assoc[eSize];
	int nSprites;

	Assets();
public:
	static Assets &instance()
	{
		static Assets instance;
		return instance;
	}
	
	unsigned Get(eSpriteFlag s);

	unsigned LoadSprite(char *path, int w, int h, eSpriteFlag s = eNone, bool center = true);

	~Assets();
};