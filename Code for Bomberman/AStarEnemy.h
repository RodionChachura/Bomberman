#pragma once
#define WIN32_LEAN_AND_MEAN

#include "baseEnemy.h"
#include <set>

namespace AStarEnemyNS
{
    const int   WIDTH = 64;                
    const int   HEIGHT = 64;               
    const int   EDGE_TOP = -20;            
    const int   EDGE_BOTTOM = 20;          
    const int   EDGE_LEFT = -20;           
    const int   EDGE_RIGHT = 20;           

    const int   COLS = 3;					
    const int   START_FRAME = 0;		    
    const int   END_FRAME = 5;				
    const float ANIMATION_DELAY = 0.2f;     
}


class AStarEnemy : public BaseEnemy
{
private:
	enum Direction{UP, DOWN, LEFT, RIGHT};
	Direction priorityDirection;
	enum ListType{OPEN, CLOSED, CLEAN};
	struct Info
	{
		int G;
		int H;
		int F;
		std::pair<int, int> parent;
		ListType listType = CLEAN;
	};
	bool success = false;
public:
    AStarEnemy();
	void setDirection(int _direction);
private:
	bool directionChecking(int parentY, int parentX, int y, int x);
	void getClosed(int &y, int &x, Info AStarMap[][MAP_WIDTH], std::set<std::pair<int, int>> &openList);
	void getOpen(int y, int x, Info AStarMap[][MAP_WIDTH], std::set<std::pair<int, int>> &openList);
	void AStar(int y, int x);
	void movementManager();
};