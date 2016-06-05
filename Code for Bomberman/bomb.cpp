#include "bomb.h"
using namespace bombNS;

Bomb::Bomb() : Entity()
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

	time = 0;
}

bool Bomb::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Bomb::startBomb(int _row, int _col)
{
	time = 0;
	row = _row;
	col = _col;
	setY(FROM_MAP(row));
	setX(FROM_MAP(col));
	tileMap[row][col] = b;
}

void Bomb::explosion()
{
	setCurrentFrame(START_FRAME + 1);
	availableToFire.push_back(std::make_pair(row, col));
	for (int i = 1; i <= fireWidth; i++)
	{
		if (tileMap[row][col + i] == __ || tileMap[row][col + i] == f || tileMap[row][col + i] == b)
			availableToFire.push_back(std::make_pair(row, col + i));
		else if (tileMap[row][col + i] == w)
		{
			availableToFire.push_back(std::make_pair(row, col + i));
			break;
		}
		else if (tileMap[row][col + i] == r)
			break;
	}
	for (int i = 1; i <= fireWidth; i++)
	{
		if (tileMap[row][col - i] == __ || tileMap[row][col - i] == f || tileMap[row][col - i] == b)
			availableToFire.push_back(std::make_pair(row, col - i));
		else if (tileMap[row][col - i] == w)
		{
			availableToFire.push_back(std::make_pair(row, col - i));
			break;
		}
		else if (tileMap[row][col - i] == r)
			break;
	}
	for (int i = 1; i <= fireWidth; i++)
	{
		if (tileMap[row + i][col] == __ || tileMap[row + i][col] == f || tileMap[row + i][col] == b)
			availableToFire.push_back(std::make_pair(row + i, col));
		else if (tileMap[row + i][col] == w)
		{
			availableToFire.push_back(std::make_pair(row + i, col));
			break;
		}
		else if (tileMap[row + i][col] == r)
			break;
	}
	for (int i = 1; i <= fireWidth; i++)
	{
		if (tileMap[row - i][col] == __ || tileMap[row - i][col] == f || tileMap[row - i][col] == b)
			availableToFire.push_back(std::make_pair(row - i, col));
		else if (tileMap[row - i][col] == w)
		{
			availableToFire.push_back(std::make_pair(row - i, col));
			break;
		}
		else if (tileMap[row - i][col] == r)
			break;
	}

	for (auto &available : availableToFire)
		tileMap[available.first][available.second] = f;
}

void Bomb::endBomb()
{
	for (auto &available : availableToFire)
		tileMap[available.first][available.second] = __;
}

void Bomb::cleaningForNextLevel()
{
	if (time < startExplosion)
		tileMap[row][col] = __;
	else 
		endBomb();
}

void Bomb::draw()
{
	if (time < startExplosion)
	{
		if(time % 200 == 0)
			setScale(SCALE);
		else if (time % 100 == 0)
			setScale(SCALE / 1.1f);
		
		Image::draw();
	}
	else
	for (auto &available : availableToFire)
	{
		setY(FROM_MAP(available.first));
		setX(FROM_MAP(available.second));
		Image::draw();
	}
}

void Bomb::update(float frameTime, bool &existance)
{
    Entity::update(frameTime);

	time++;
	if (time < startExplosion)
		setCurrentFrame(START_FRAME);
	if (tileMap[row][col] == f && !bombInFire && time < startExplosion)
	{
		if(time < startExplosion - delayExplosion)
			time = startExplosion - delayExplosion;
		bombInFire = true;
	}
	if (time == startExplosion)
		explosion();

	if (currentFrame == END_FRAME)
	{
		endBomb();
		existance = false;
	}
}
