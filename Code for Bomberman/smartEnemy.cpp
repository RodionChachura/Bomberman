#include "smartEnemy.h"
using namespace smartEnemyNS;

SmartEnemy::SmartEnemy() : BaseEnemy()
{
    spriteData.width = WIDTH;           
    spriteData.height = HEIGHT;
    spriteData.rect.bottom = HEIGHT;    
    spriteData.rect.right = WIDTH;
    edge.top    = EDGE_TOP;             
    edge.bottom = EDGE_BOTTOM;
    edge.left   = EDGE_LEFT;
    edge.right  = EDGE_RIGHT;

    collisionType = entityNS::BOX;
	bombDestroyer = false;
}

void SmartEnemy::movementManager()
{
	if (abs(getCenterX() - initialX) > TEXTURE_SIZE || abs(getCenterY() - initialY) > TEXTURE_SIZE)
	{
		if (path.empty())
		{
			movement = &SmartEnemy::noMovement;
			makeFalse();
			find(IN_MAP(getCenterX()), IN_MAP(getCenterY()));
		}
		else
		{
			setX(FROM_MAP(IN_MAP(getCenterX())));
			setY(FROM_MAP(IN_MAP(getCenterY())));
			initialX = getCenterX();
			initialY = getCenterY();
			movePointer tempMove = path.back();
			movement = tempMove;
			path.pop_back();
		}
	}
}

void SmartEnemy::makeFalse()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			boolMap[i][j] = false;
}

bool SmartEnemy::find(int x, int y)
{
	if (x == manX && y == manY)
		return true;

	if (tileMap[y][x] == r || tileMap[y][x] == w || boolMap[y][x])
		return false;

	boolMap[y][x] = true;

	if (x <= manX && y >= manY)
	{
		if (x == manX)
		{
			if (find(x + 1, y))
			{path.push_back(&SmartEnemy::right); return true;}
			if (find(x, y - 1))
			{path.push_back(&SmartEnemy::up); return true;}
		}
		else
		{
			if (find(x, y - 1))
			{path.push_back(&SmartEnemy::up); return true;}
			if (find(x + 1, y))
			{path.push_back(&SmartEnemy::right); return true;}
		}
		if (find(x - 1, y))
		{path.push_back(&SmartEnemy::left); return true;}
		if (find(x, y + 1))
		{path.push_back(&SmartEnemy::down); return true;}
	}

	if (x <= manX && y <= manY)
	{
		if (y == manY)
		{
			if (find(x, y + 1))
			{path.push_back(&SmartEnemy::down); return true;}
			if (find(x + 1, y))
			{path.push_back(&SmartEnemy::right); return true;}
		}
		else
		{
			if (find(x + 1, y))
			{path.push_back(&SmartEnemy::right); return true;}
			if (find(x, y + 1))
			{path.push_back(&SmartEnemy::down); return true;}
		}
		if (find(x - 1, y))
		{path.push_back(&SmartEnemy::left); return true;}
		if (find(x, y - 1))
		{path.push_back(&SmartEnemy::up); return true;}
	}

	if (x >= manX && y >= manY)
	{
		if (x == manX)
		{
			if (find(x - 1, y))
			{path.push_back(&SmartEnemy::left); return true;}
			if (find(x, y - 1))
			{path.push_back(&SmartEnemy::up); return true;}
		}
		else
		{
			if (find(x, y - 1))
			{path.push_back(&SmartEnemy::up); return true;}
			if (find(x - 1, y))
			{path.push_back(&SmartEnemy::left); return true;}
		}
		if (find(x + 1, y))
		{path.push_back(&SmartEnemy::right); return true;}
		if (find(x, y + 1))
		{path.push_back(&SmartEnemy::down); return true;}
	}

	if (x >= manX && y <= manY)
	{
		if (y == manY)
		{
			if (find(x, y + 1))
			{path.push_back(&SmartEnemy::down); return true;}
			if (find(x - 1, y))
			{path.push_back(&SmartEnemy::left); return true;}
		}
		else
		{
			if (find(x - 1, y))
			{path.push_back(&SmartEnemy::left); return true;}
			if (find(x, y + 1))
			{path.push_back(&SmartEnemy::down); return true;}
		}
		if (find(x + 1, y))
		{path.push_back(&SmartEnemy::right); return true;}
		if (find(x, y - 1))
		{path.push_back(&SmartEnemy::up); return true;}
	}
	return false;
}

