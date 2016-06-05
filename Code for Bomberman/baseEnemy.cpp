#include "baseEnemy.h"

void BaseEnemy::update(float frameTime, int _manX, int _manY)
{
    Entity::update(frameTime);
	manX = _manX; manY = _manY;
	movementManager();
	(*this.*movement)(frameTime);
}

bool BaseEnemy::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void BaseEnemy::up(float frameTime)
{
	setY(getY() - frameTime * speed);
}
void BaseEnemy::down(float frameTime)
{
	setY(getY() + frameTime * speed);
}
void BaseEnemy::right(float frameTime)
{
	setX(getX() + frameTime * speed);
}
void BaseEnemy::left(float frameTime)
{
	setX(getX() - frameTime * speed);
}

bool BaseEnemy::checkUp(int tile)
{
	return tileMap[IN_MAP(getY() - 0.1f)][IN_MAP(getX() + 0.5f)] == tile &&
		   tileMap[IN_MAP(getY() - 0.1f)][IN_MAP(getX() + TEXTURE_SIZE - 0.5f)] == tile;
}
bool BaseEnemy::checkDown(int tile)
{
	return tileMap[IN_MAP(getY() + TEXTURE_SIZE + 0.1f)][IN_MAP(getX() + 0.5f)] == tile &&
		   tileMap[IN_MAP(getY() + TEXTURE_SIZE + 0.1f)][IN_MAP(getX() + TEXTURE_SIZE - 0.5f)] == tile;
}
bool BaseEnemy::checkRight(int tile)
{
	return tileMap[IN_MAP(getY() + 0.5f)][IN_MAP((getX() + TEXTURE_SIZE + 0.1f))] == tile &&
		   tileMap[IN_MAP(getY() + TEXTURE_SIZE - 0.5f)][IN_MAP((getX() + TEXTURE_SIZE + 0.1f))] == tile;
}
bool BaseEnemy::checkLeft(int tile)
{
	return tileMap[IN_MAP(getY() + 0.5f)][IN_MAP(getX() - 0.1f)] == tile &&
		   tileMap[IN_MAP(getY() + TEXTURE_SIZE - 0.5f)][IN_MAP(getX() - 0.1f)] == tile;
}

