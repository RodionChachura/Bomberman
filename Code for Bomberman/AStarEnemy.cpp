#include "AStarEnemy.h"
using namespace AStarEnemyNS;

AStarEnemy::AStarEnemy() : BaseEnemy()
{
    spriteData.width = WIDTH;           
    spriteData.height = HEIGHT;
    spriteData.rect.bottom = HEIGHT;    
    spriteData.rect.right = WIDTH;
    edge.top    = EDGE_TOP;            
    edge.bottom = EDGE_BOTTOM;
    edge.left   = EDGE_LEFT;
    edge.right  = EDGE_RIGHT;

    frameDelay = ANIMATION_DELAY;
    startFrame = START_FRAME;    
    endFrame     = END_FRAME;     
    currentFrame = startFrame;

    collisionType = entityNS::BOX;
	bombDestroyer = true;
}

bool AStarEnemy::directionChecking(int parentY, int parentX, int y, int x)
{
	switch (priorityDirection)
	{
	case UP:    if (parentY > y) return true;
	case DOWN:  if (parentY < y) return true;
	case LEFT:  if (parentX > x) return true;
	case RIGHT: if (parentX < x) return true;
	}

	return false;
}

void AStarEnemy::getClosed(int &y, int &x, Info AStarMap[][MAP_WIDTH], std::set<std::pair<int, int>> &openList)
{
	int minF = INT_MAX;
	int minPosition = 0;
	for (auto &open : openList)
	{
		if (AStarMap[open.first][open.second].F < minF)
		{
			minF = AStarMap[open.first][open.second].F;
			y = open.first;
			x = open.second;
		}
	}
	for (auto &open : openList)
	{
		if (AStarMap[open.first][open.second].F == minF &&
			directionChecking(AStarMap[open.first][open.second].parent.first, 
							  AStarMap[open.first][open.second].parent.second, y, x))
		{
			y = open.first;
			x = open.second;
			break;
		}
	}
	openList.erase(std::make_pair(y, x));

	AStarMap[y][x].listType = CLOSED;
	if (y == manY && x == manX)
		success = true;
}

void AStarEnemy::getOpen(int y, int x, Info AStarMap[][MAP_WIDTH], std::set<std::pair<int, int>> &openList)
{
	if (tileMap[y - 1][x] ==__ || tileMap[y - 1][x] == f || tileMap[y - 1][x] == b)
	{
		if (AStarMap[y - 1][x].listType == CLEAN
		|| (AStarMap[y - 1][x].listType == OPEN && AStarMap[y - 1][x].H > AStarMap[y][x].H + 1))
		{
			openList.insert(std::make_pair(y - 1, x));
			AStarMap[y - 1][x].G = AStarMap[y][x].G + 1;
			AStarMap[y - 1][x].H = abs(y - 1 - manY) + abs(x - manX);
			AStarMap[y - 1][x].F = AStarMap[y - 1][x].G + AStarMap[y - 1][x].H;
			AStarMap[y - 1][x].parent = std::make_pair(y, x);
			AStarMap[y - 1][x].listType = OPEN;
		}
	}
	if (tileMap[y + 1][x] ==__ || tileMap[y + 1][x] == f || tileMap[y + 1][x] == b)
	{
		if (AStarMap[y + 1][x].listType == CLEAN
		||  (AStarMap[y + 1][x].listType == OPEN && AStarMap[y + 1][x].H > AStarMap[y][x].H + 1))
		{
			openList.insert(std::make_pair(y + 1, x));
			AStarMap[y + 1][x].G = AStarMap[y][x].G + 1;
			AStarMap[y + 1][x].H = abs(y + 1 - manY) + abs(x - manX);
			AStarMap[y + 1][x].F = AStarMap[y + 1][x].G + AStarMap[y + 1][x].H;
			AStarMap[y + 1][x].parent = std::make_pair(y, x);
			AStarMap[y + 1][x].listType = OPEN;
		}
	}
	if (tileMap[y][x - 1] ==__ || tileMap[y][x - 1] == f || tileMap[y][x - 1] == b)
	{
		if (AStarMap[y][x - 1].listType == CLEAN
		||  (AStarMap[y][x - 1].listType == OPEN && AStarMap[y][x - 1].H > AStarMap[y][x].H + 1))
		{
			openList.insert(std::make_pair(y, x - 1));
			AStarMap[y][x - 1].G = AStarMap[y][x].G + 1;
			AStarMap[y][x - 1].H = abs(y - manY) + abs(x - 1 - manX);
			AStarMap[y][x - 1].F = AStarMap[y][x - 1].G + AStarMap[y][x - 1].H;
			AStarMap[y][x - 1].parent = std::make_pair(y, x);
			AStarMap[y][x - 1].listType = OPEN;
		}
	}
	if (tileMap[y][x + 1] ==__ || tileMap[y][x + 1] == f || tileMap[y][x + 1] == b)
	{
		if (AStarMap[y][x + 1].listType == CLEAN
		||  (AStarMap[y][x + 1].listType == OPEN && AStarMap[y][x + 1].H > AStarMap[y][x].H + 1))
		{
			openList.insert(std::make_pair(y, x + 1));
			AStarMap[y][x + 1].G = AStarMap[y][x].G + 1;
			AStarMap[y][x + 1].H = abs(y - manY) + abs(x + 1 - manX);
			AStarMap[y][x + 1].F = AStarMap[y][x + 1].G + AStarMap[y][x + 1].H;
			AStarMap[y][x + 1].parent = std::make_pair(y, x);
			AStarMap[y][x + 1].listType = OPEN;
		}
	}
}

void AStarEnemy::AStar(int y, int x)
{
	success = false;
	std::set<std::pair<int, int>> openList;
	Info AStarMap[MAP_HEIGHT][MAP_WIDTH]{};

	AStarMap[y][x].G = 0;
	AStarMap[y][x].H = abs(y - manY) + abs(x - manX);
	AStarMap[y][x].F = AStarMap[y][x].H;
	AStarMap[y][x].parent = std::make_pair(0, 0);
	AStarMap[y][x].listType = CLOSED;
	
	int insideLoopY = y;
	int insideLoopX = x;
	getOpen(insideLoopY, insideLoopX, AStarMap, openList);
	do{
		getClosed(insideLoopY, insideLoopX, AStarMap, openList);
		getOpen(insideLoopY, insideLoopX, AStarMap, openList);
	} while (!openList.empty() && !success);

	if (success)
	{
		int nearistY = manY; int nearistX = manX;
		while (!(AStarMap[nearistY][nearistX].parent.first == y &&  AStarMap[nearistY][nearistX].parent.second == x))
		{
			std::pair<int, int> temp = AStarMap[nearistY][nearistX].parent;
			nearistY = temp.first;
			nearistX = temp.second;
		}
		if (nearistY < y)
			movement = &AStarEnemy::up;
		else if (nearistY > y)
			movement = &AStarEnemy::down;
		else if (nearistX < x)
			movement = &AStarEnemy::left;
		else if (nearistX > x)
			movement = &AStarEnemy::right;
	}
	else
		movement = &AStarEnemy::noMovement;
}

void AStarEnemy::movementManager()
{
	if (abs(getCenterX() - initialX) > TEXTURE_SIZE || abs(getCenterY() - initialY) > TEXTURE_SIZE || movement == &AStarEnemy::noMovement)
	{
		setX(FROM_MAP(IN_MAP(getCenterX())));
		setY(FROM_MAP(IN_MAP(getCenterY())));
		initialX = getCenterX();
		initialY = getCenterY();
		AStar(IN_MAP(initialY), IN_MAP(initialX));
	}
}

void AStarEnemy::setDirection(int _direction)
{
	switch (_direction)
	{
	case 0: priorityDirection = UP; break;
	case 1: priorityDirection = DOWN; break;
	case 2: priorityDirection = LEFT; break;
	case 3: default: priorityDirection = RIGHT; break;
	}
}

