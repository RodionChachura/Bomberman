#pragma once      
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <ctime>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <vector>
#include "game.h"
#include "textureManager.h"
#include "textureManagers.h"
#include "image.h"
#include "textDX.h"
#include "man.h"
#include "bomb.h"
#include "map.h"
#include "enemy.h"
#include "smartEnemy.h"
#include "AStarEnemy.h"
#include "levelManager.h"

#define GAME_COMPLEXITY 12
#define FINAL_DELAY     1000

class Bomberman : public Game
{
private:
	TextureManagers textureManagers;

	TextDX *dxFont64;

	Image   background;
	Image   rock;
	Image   wood;
	Image   bonusheart;
	Image   bonusbomb;
	Image   bonusexplosion;

	Bomb    bomb;
	Man		man;

	enum Bonus {LIVE, BOMB, EXPLOSION};

	std::vector<Bomb> bombs;
	std::vector<BaseEnemy*> baseEnemies;
	std::vector < std::pair<Bonus, std::pair<int, int>>> bonusVector;

	size_t numberOfBombs;
	int currentLevel;
	int endTime;

public:
    Bomberman();
    virtual ~Bomberman();

	void getLevel(bool play);                                                             
	void readMapFromFile(int enemiesSpeed, int smartEnemiesSpeed, int aStarEnemiesSpeed);                                                ///
	void getLevelBonusGenerator(int liveBonus, int bombBonus, int explosionBonus);  
	
	void endTimer(bool start);
    void initialize(HWND hwnd);
	void ai();
    void update();               
    void collisions();  
    void render();      
    void releaseAll();
    void resetAll();
};
