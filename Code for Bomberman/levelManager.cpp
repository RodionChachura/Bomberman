#include "bomberman.h"

void Bomberman::getLevelBonusGenerator(int liveBonus, int bombBonus, int explosionBonus)
{
	bonusVector.clear(); 
	std::vector<std::pair<int, int>> woodbricks;

	for(int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			if (tileMap[i][j] == w)
				woodbricks.push_back(std::make_pair(i, j));

	srand((unsigned int)time(0));
	for (int i = 0; i < liveBonus; i++)
	{
		if (woodbricks.size() == 0)
			break;
		else
		{
			int randomBrick = rand() % woodbricks.size();
			bonusVector.push_back(std::make_pair(LIVE, woodbricks[randomBrick]));
			woodbricks.erase(woodbricks.begin() + randomBrick);
		}
	}
	for (int i = 0; i < bombBonus; i++)
	{
		if (woodbricks.size() == 0)
			break;
		else
		{
			int randomBrick = rand() % woodbricks.size();
			bonusVector.push_back(std::make_pair(BOMB, woodbricks[randomBrick]));
			woodbricks.erase(woodbricks.begin() + randomBrick);
		}
	}
	for (int i = 0; i < explosionBonus; i++)
	{
		if (woodbricks.size() == 0)
			break;
		else
		{
			int randomBrick = rand() % woodbricks.size();
			bonusVector.push_back(std::make_pair(EXPLOSION, woodbricks[randomBrick]));
			woodbricks.erase(woodbricks.begin() + randomBrick);
		}
	}
}

void Bomberman::readMapFromFile(int enemiesSpeed, int smartEnemiesSpeed, int aStarEnemiesSpeed)
{
	std::string path = "levels\\level" + std::to_string(currentLevel) + ".txt";
	std::ifstream file(path);
	if(!file.is_open())
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error occured in " + path));
	std::stringstream str;
	str << file.rdbuf();
	
	int row = 0; int col = 0;
	for (auto &c : str.str())
	{
		switch (c)
		{
		case 'r':
			tileMap[row][col] = r;
			break;
		case 'w':
			tileMap[row][col] = w;
			break;
		case '\b':
			tileMap[row][col] = __;
			break;
		case 'm':
			tileMap[row][col] = __;
			man.setY(FROM_MAP(row));
			man.setX(FROM_MAP(col));
			break;
		case 'e':
			tileMap[row][col] = __;
			baseEnemies.push_back(new Enemy());
			if (!baseEnemies[baseEnemies.size() - 1]->
				initialize(this, 
					enemyNS::WIDTH, 
					enemyNS::HEIGHT, 
					enemyNS::COLS, 
					textureManagers.getTexture("enemy")))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
			baseEnemies[baseEnemies.size() - 1]->setSpeed(enemiesSpeed);
			baseEnemies[baseEnemies.size() - 1]->setY(FROM_MAP(row));
			baseEnemies[baseEnemies.size() - 1]->setX(FROM_MAP(col));
			break;
		case 's':
			tileMap[row][col] = __;
			baseEnemies.push_back(new SmartEnemy());
			if (!baseEnemies[baseEnemies.size() - 1]->
				initialize(this, 
					smartEnemyNS::WIDTH, 
					smartEnemyNS::HEIGHT, 
					TEXTURE_COLS, 
					textureManagers.getTexture("smartEnemy")))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
			baseEnemies[baseEnemies.size() - 1]->setSpeed(smartEnemiesSpeed);
			baseEnemies[baseEnemies.size() - 1]->setY(FROM_MAP(row));
			baseEnemies[baseEnemies.size() - 1]->setX(FROM_MAP(col));
			break;
		case 'a':
			tileMap[row][col] = __;
			baseEnemies.push_back(new AStarEnemy());
			if (!baseEnemies[baseEnemies.size() - 1]->
				initialize(this, 
					AStarEnemyNS::WIDTH, 
					AStarEnemyNS::HEIGHT, 
					AStarEnemyNS::COLS, 
					textureManagers.getTexture("AStarEnemy")))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
			baseEnemies[baseEnemies.size() - 1]->setSpeed(aStarEnemiesSpeed);
			baseEnemies[baseEnemies.size() - 1]->setY(FROM_MAP(row));
			baseEnemies[baseEnemies.size() - 1]->setX(FROM_MAP(col));
			((AStarEnemy*)baseEnemies[baseEnemies.size() - 1])->setDirection(baseEnemies.size() % 4);
			break;
		case '\n':
			row++;
			col = -1;
			break;
		default:
			tileMap[row][col] = __;
			break;
		}
		col++;
	}
	file.close();
}

void Bomberman::getLevel(bool play)
{
	baseEnemies.clear();
	for (auto & bomb : bombs)
		bomb.cleaningForNextLevel();
	bombs.clear();


	currentLevel++;
	if (!play)
	{
		currentLevel = 0;
		endTimer(true);
	}
	man.increaseSpeed(10);
	bomb.fireWidth = (currentLevel < 3) ? 1 : 2;
	numberOfBombs  = (currentLevel < 3) ? 1 : (currentLevel < 5)? 2 : 3;
	man.lives      = (currentLevel < 5) ? 2 : 3;
	static int enemiesSpeed      = 50 + currentLevel * GAME_COMPLEXITY;
	static int smartEnemiesSpeed = 40 + currentLevel * GAME_COMPLEXITY;
	static int aStarEnemiesSpeed = 30 + currentLevel * GAME_COMPLEXITY;
	static int liveBonus = currentLevel;
	static int bombBonus = currentLevel;
	static int explosionBonus = currentLevel;


	readMapFromFile(enemiesSpeed, smartEnemiesSpeed, aStarEnemiesSpeed);

	getLevelBonusGenerator(liveBonus, bombBonus, explosionBonus);
}
