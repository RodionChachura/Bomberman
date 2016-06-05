#include "enemy.h"
using namespace enemyNS;

Enemy::Enemy() : BaseEnemy()
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
	bombDestroyer = false;
}

void Enemy::randomDirection()
{
	std::vector<movePointer> direction;

	if (checkUp(__)    || checkUp(f))
		direction.push_back(&Enemy::up);
	if (checkDown(__)  || checkDown(f))
		direction.push_back(&Enemy::down);
	if (checkRight(__) || checkRight(f))
		direction.push_back(&Enemy::right);
	if (checkLeft(__)  || checkLeft(f))
		direction.push_back(&Enemy::left);

	/*switch (direction.size())
	{
	case 0:
		movement = &Enemy::noMovement;
		break;
	case 1:
		movement = direction[0];
		break;
	case 2:
		movement = direction[rand() % 2];
		break;
	case 3: case 4:
		for (unsigned int i = 0; i < direction.size(); i++)
		{
			if (direction[i] == movement)
			{
				direction.erase(direction.begin() + i);
				break;
			}
		}
		movement = direction[rand() % direction.size()];
		break;
	}*/
	if(direction.size() == 0)
		movement = &Enemy::noMovement;
	else
		movement = direction[rand() % direction.size()];
}

void Enemy::movementManager()
{
	//int randomInterval = rand() % 5 + 1;
	if (abs(getX() - initialX) > TEXTURE_SIZE || abs(getY() - initialY) > TEXTURE_SIZE || movement == &Enemy::noMovement)
	{
		setX(FROM_MAP(IN_MAP(getCenterX())));
		setY(FROM_MAP(IN_MAP(getCenterY())));
		initialX = getX();
		initialY = getY();
		randomDirection();
	}
}

