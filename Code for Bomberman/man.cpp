#include "man.h"
using namespace manNS;

Man::Man() : Entity()
{
    spriteData.width = WIDTH;           
    spriteData.height = HEIGHT;

	frameDelay = ANIMATION_DELAY;
    edge.top    = EDGE_TOP;             
    edge.bottom = EDGE_BOTTOM;
    edge.left   = EDGE_LEFT;
    edge.right  = EDGE_RIGHT;

    collisionType = entityNS::BOX;
}

bool Man::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Man::up(float frameTime)
{
	setY(getY() - frameTime * speed);
	noMovement = 0;
	if (currentFrame < 12)
	{
		setFrames(12, 15);
		setCurrentFrame(12);
	}
}
void Man::down(float frameTime)
{
	setY(getY() + frameTime * speed);
	if (currentFrame > 3 || noMovement > 50)
	{
		setFrames(0, 3);
		setCurrentFrame(0);
	}
	noMovement = 0;
}
void Man::right(float frameTime)
{
	setX(getX() + frameTime * speed);
	noMovement = 0;
	if (currentFrame < 8 || currentFrame > 11)
	{
		setFrames(8, 11);
		setCurrentFrame(8);
	}
}
void Man::left(float frameTime)
{
	setX(getX() - frameTime * speed);
	noMovement = 0;
	if (currentFrame < 4 || currentFrame > 7)
	{
		setFrames(4, 7);
		setCurrentFrame(4);
	}
}

bool Man::checkUp(int tile)
{
	return tileMap[IN_MAP(getY())][IN_MAP(getX() + 1)] == tile &&
		   tileMap[IN_MAP(getY())][IN_MAP(getX() + TEXTURE_SIZE - 1)] == tile;
}
bool Man::checkDown(int tile)
{
	return tileMap[IN_MAP(getY() + TEXTURE_SIZE)][IN_MAP(getX() + 1)] == tile &&
		   tileMap[IN_MAP(getY() + TEXTURE_SIZE)][IN_MAP(getX() + TEXTURE_SIZE - 1)] == tile;
}
bool Man::checkRight(int tile)
{
	return tileMap[IN_MAP((getY() + 1))][IN_MAP(getX() + TEXTURE_SIZE)] == tile &&
		tileMap[IN_MAP(getY() + TEXTURE_SIZE - 1)][IN_MAP(getX() + TEXTURE_SIZE)] == tile;
}
bool Man::checkLeft(int tile)
{
	return tileMap[IN_MAP((getY() + 1))][IN_MAP(getX())] == tile &&
		   tileMap[IN_MAP(getY() + TEXTURE_SIZE - 1)][IN_MAP(getX())] == tile;
}
bool Man::checkCenter(int tile)
{
	return tileMap[IN_MAP(getCenterY())][IN_MAP(getCenterX())] == tile;
}

void Man::moveUp(float frameTime)
{
	if (checkUp(__) || checkUp(f) || (checkUp(b) && checkCenter(b)))
		up(frameTime);
	else if (!input->isKeyDown(RIGHT_KEY) && !input->isKeyDown(DOWN_KEY) && !input->isKeyDown(LEFT_KEY) &&
			tileMap[IN_MAP(getY() - 1)][IN_MAP(getCenterX())] == __ &&
			tileMap[IN_MAP(getY() - 1)][IN_MAP(getX() + TEXTURE_SIZE)] != __)
		moveLeft(frameTime);
	else if (!input->isKeyDown(RIGHT_KEY) && !input->isKeyDown(DOWN_KEY) && !input->isKeyDown(LEFT_KEY) &&
			tileMap[IN_MAP(getY() - 1)][IN_MAP(getCenterX())] == __ &&
			tileMap[IN_MAP(getY() - 1)][IN_MAP(getX())] != __)
		moveRight(frameTime);
}
void Man::moveDown(float frameTime)
{
	if (checkDown(__) || checkDown(f) || (checkDown(b) && checkCenter(b)))
		down(frameTime);
	else if (!input->isKeyDown(RIGHT_KEY) && !input->isKeyDown(UP_KEY) && !input->isKeyDown(LEFT_KEY) &&
			tileMap[IN_MAP(getY() + TEXTURE_SIZE + 1)][IN_MAP(getCenterX())] == __ &&
			tileMap[IN_MAP(getY() + TEXTURE_SIZE + 1)][IN_MAP(getX() + TEXTURE_SIZE)] != __)
		moveLeft(frameTime);
	else if (!input->isKeyDown(RIGHT_KEY) && !input->isKeyDown(UP_KEY) && !input->isKeyDown(LEFT_KEY) &&
			tileMap[IN_MAP(getY() + TEXTURE_SIZE + 1)][IN_MAP(getCenterX())] == __ &&
			tileMap[IN_MAP(getY() + TEXTURE_SIZE + 1)][IN_MAP(getX())] != __)
		moveRight(frameTime);
}
void Man::moveRight(float frameTime)
{
	if (checkRight(__) || checkRight(f) || (checkRight(b) && checkCenter(b)))
		right(frameTime);
	else if (!input->isKeyDown(DOWN_KEY) && !input->isKeyDown(UP_KEY) && !input->isKeyDown(LEFT_KEY) &&
			tileMap[IN_MAP(getCenterY())][IN_MAP(getX() + TEXTURE_SIZE + 1)] == __ &&
			tileMap[IN_MAP(getY() + TEXTURE_SIZE)][IN_MAP(getX() + TEXTURE_SIZE + 1)] != __)
		moveUp(frameTime);
	else if (!input->isKeyDown(DOWN_KEY) && !input->isKeyDown(UP_KEY) && !input->isKeyDown(LEFT_KEY) &&
			tileMap[IN_MAP(getCenterY())][IN_MAP(getX() + TEXTURE_SIZE + 1)] == __ &&
			tileMap[IN_MAP(getY())][IN_MAP(getX() + TEXTURE_SIZE + 2)] != __)
		moveDown(frameTime);
}
void Man::moveLeft(float frameTime)
{
	if (checkLeft(__) || checkLeft(f) || (checkLeft(b) && checkCenter(b)))
		left(frameTime);
	else if (!input->isKeyDown(DOWN_KEY) && !input->isKeyDown(UP_KEY) && !input->isKeyDown(RIGHT_KEY) &&
			tileMap[IN_MAP(getCenterY())][IN_MAP(getX() - 1)] == __ &&
			tileMap[IN_MAP(getY() + TEXTURE_SIZE)][IN_MAP(getX() - 1)] != __)
		moveUp(frameTime);
	else if (!input->isKeyDown(DOWN_KEY) && !input->isKeyDown(UP_KEY) && !input->isKeyDown(RIGHT_KEY) &&
			tileMap[IN_MAP(getCenterY())][IN_MAP(getX() - 1)] == __ &&
			tileMap[IN_MAP(getY())][IN_MAP(getX() - 1)] != __)
		moveDown(frameTime);
}

void Man::decreaseLives()
{
	if (!unvulnerability)
	{
		lives--;
		setActive(false);
	}
}

void Man::noMovementTimer()
{
	noMovement++;
	if (noMovement > 50)
	{
		setCurrentFrame(0);
		setFrames(0, 0);
	}
}

void Man::unvulnerabilityTimer()
{
	if(!getActive())
		unvulnerability++;
	if (unvulnerability == 500)
	{
		activate();
		unvulnerability = 0;
	}
}

void Man::update(float frameTime)
{
    Entity::update(frameTime);
	unvulnerabilityTimer();
}
