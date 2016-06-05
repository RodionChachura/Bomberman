#pragma once
#define WIN32_LEAN_AND_MEAN

#include "BaseEnemy.h"

namespace enemyNS
{
    const int   WIDTH = 64;                
    const int   HEIGHT = 64;               
    const int   EDGE_TOP = -20;            
    const int   EDGE_BOTTOM = 20;          
    const int   EDGE_LEFT = -20;           
    const int   EDGE_RIGHT = 20;           

    const int   COLS = 4;					
    const int   START_FRAME = 0;		   
    const int   END_FRAME = 3;				
    const float ANIMATION_DELAY = 1.0f;    
}


class Enemy : public BaseEnemy
{
public:
    Enemy();
private:
	void randomDirection();
	void movementManager();
};

