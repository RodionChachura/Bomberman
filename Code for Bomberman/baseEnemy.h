#pragma once
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "map.h"
#include <set>

class BaseEnemy : public Entity
{
protected:
	typedef void (BaseEnemy::*movePointer)(float);
	movePointer movement = &BaseEnemy::noMovement;
	bool bombDestroyer;
	float initialX;
	float initialY;
	int manX;
	int manY;
	int speed;
public:
	BaseEnemy() :Entity() {};
	void update(float frameTime, int _manX, int _manY);
	virtual void movementManager() = 0;
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	inline virtual void increaseSpeed(int growth) { speed += growth; }
	inline void setSpeed(int _speed) { speed = _speed; }
	inline bool canDestroyBomb() { return bombDestroyer; }
protected:
	void up(float frameTime);
	void down(float frameTime);
	void right(float frameTime);
	void left(float frameTime);
	inline void noMovement(float frameTime) {}

	virtual bool checkUp(int tile);
	virtual bool checkDown(int tile);
	virtual bool checkRight(int tile);
	virtual bool checkLeft(int tile);
};