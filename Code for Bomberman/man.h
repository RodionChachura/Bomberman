#pragma once
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "map.h"


namespace manNS
{
  const int	WIDTH = 64;                   
  const int	HEIGHT = 64;                  
  const int	START_FRAME = 0;
  const int	END_FRAME = 15;
  const float ANIMATION_DELAY = 0.3f;
  const float delayConst = 30.f;
  const int	COLS = 4;
  const float ROTATION_RATE = 180.0f;
  const float SCALE_RATE = 0.2f;
  const float SCALE = 1.0f;

  const int   EDGE_TOP = -20;             
  const int   EDGE_BOTTOM = 20;           
  const int   EDGE_LEFT = -20;            
  const int   EDGE_RIGHT = 20;

}


class Man : public Entity
{
private:
	int unvulnerability = 0;
	int noMovement = 0;
	int speed = 110;
public:
    int lives = 1;

    Man();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);

private:
	void up(float frameTime);
	void down(float frameTime);
	void right(float frameTime);
	void left(float frameTime);

	bool checkUp(int tile);
	bool checkDown(int tile);
	bool checkRight(int tile);
	bool checkLeft(int tile);


public:
	inline void increaseSpeed(int growth) { speed += growth; frameDelay = manNS::delayConst / speed; }
	bool checkCenter(int tile);
	void moveUp(float frameTime);
	void moveDown(float frameTime);
	void moveRight(float frameTime);
	void moveLeft(float frameTime);

	void decreaseLives();
	void noMovementTimer();
	void unvulnerabilityTimer();
    void update(float frameTime);
};
