#pragma once
#define WIN32_LEAN_AND_MEAN

#include "baseEnemy.h"

namespace smartEnemyNS
{
    const int   WIDTH = 64;               
    const int   HEIGHT = 64;              
    const int   EDGE_TOP = -20;           
    const int   EDGE_BOTTOM = 20;         
    const int   EDGE_LEFT = -20;          
    const int   EDGE_RIGHT = 20;          
}


class SmartEnemy : public BaseEnemy
{
private:
	std::vector<movePointer> path;
	bool boolMap[MAP_HEIGHT][MAP_WIDTH]{};
public:
    SmartEnemy();
private:
	void makeFalse();
	bool find(int x, int y);
	void movementManager();
};