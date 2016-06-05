#pragma once
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "entity.h"
#include "constants.h"
#include "map.h"

namespace bombNS
{
    const int	WIDTH = 64;               
    const int	HEIGHT = 64;              
	const float SCALE = 1.0f;

	const int   EDGE_TOP = -20;           
    const int   EDGE_BOTTOM = -20;        
    const int   EDGE_LEFT = -20;          
    const int   EDGE_RIGHT = 20;

	const int   COLS = 4;					
    const int   START_FRAME = 0;		    
    const int   END_FRAME = 15;				
    const float ANIMATION_DELAY = 0.025f;  

	const int startExplosion = 600;
	const int delayExplosion = 200;

}

class Bomb : public Entity
{
private:
	std::vector<std::pair<int, int>> availableToFire;
	int time;
	int row;
	int col;
	bool bombInFire = false;
public:
	int fireWidth = 2;

    Bomb();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);

	void startBomb(int _row, int _col);
	void explosion();
	void endBomb();
	void cleaningForNextLevel();
	void draw();
    void update(float frameTime, bool &existance);
};
