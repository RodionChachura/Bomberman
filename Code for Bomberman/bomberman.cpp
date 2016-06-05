#include "bomberman.h"

Bomberman::Bomberman() : Game()
{
	dxFont64    = new TextDX();
	numberOfBombs = 2;
	currentLevel = 1;
	endTime = 0;
}

Bomberman::~Bomberman()
{
	for (auto &enemy : baseEnemies)
		SAFE_DELETE(enemy);
	SAFE_DELETE(dxFont64);
	releaseAll();           
}

void Bomberman::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	textureManagers.initialize(graphics);

	if(!dxFont64->initialize(graphics, 64, false, false, "Arial"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	
	textureManagers.add("rock", ROCK_IMAGE);
	textureManagers.add("wood", WOOD_IMAGE);
	textureManagers.add("bomb", BOMB_IMAGE);
	textureManagers.add("heart", HEART_IMAGE);
	textureManagers.add("bonusBomb", BONUSBOMB_IMAGE);
	textureManagers.add("bonusExplosion", BONUSEXPLOSION_IMAGE);
	textureManagers.add("backGround", BACKGROUND_IMAGE);
	textureManagers.add("man", MAN_IMAGE);
	textureManagers.add("enemy", ENEMY_IMAGE);
	textureManagers.add("smartEnemy", SMARTENEMY_IMAGE);
	textureManagers.add("AStarEnemy", ASTARENEMY_IMAGE);

	if (!background.initialize(graphics, 0, 0, 0, textureManagers.getTexture("backGround")))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	if (!rock.initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_COLS, textureManagers.getTexture("rock")))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing rock"));
	if (!wood.initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_COLS, textureManagers.getTexture("wood")))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wood"));
	if (!bomb.initialize(this, TEXTURE_SIZE, TEXTURE_SIZE, bombNS::COLS, textureManagers.getTexture("bomb")))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bomb"));
	if (!bonusheart.initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_COLS, textureManagers.getTexture("heart")))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart"));
	if (!bonusbomb.initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_COLS, textureManagers.getTexture("bonusBomb")))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bonusbomb"));
	if (!bonusexplosion.initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_COLS, textureManagers.getTexture("bonusExplosion")))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bonusexplosion"));
	if (!man.initialize(this, manNS::WIDTH, manNS::HEIGHT, manNS::COLS, textureManagers.getTexture("man")))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing man"));

	getLevel(true);

	return;
}

void Bomberman::update()
{
	if (input->isKeyDown(RIGHT_KEY))	 man.moveRight(frameTime);
	if (input->isKeyDown(LEFT_KEY))		 man.moveLeft(frameTime);
	if (input->isKeyDown(UP_KEY))		 man.moveUp(frameTime);
	if (input->isKeyDown(DOWN_KEY))		 man.moveDown(frameTime);
	if (!input->anyKeyPressed())         man.noMovementTimer();
	if (input->isKeyDown(BACKSPACE_KEY) && bombs.size() < numberOfBombs && !man.checkCenter(b))
	{
		bomb.startBomb(IN_MAP(man.getCenterY()), IN_MAP(man.getCenterX()));
		bombs.push_back(bomb);
	}

	man.update(frameTime);
	for (size_t i = 0; i < bombs.size(); i++)
	{
		bool existance = true;
		bombs[i].update(frameTime, existance);
		if (existance == false)
		{
			bombs.erase(bombs.begin() + i);
			i--;
		}
	}

	for (auto &enemy : baseEnemies)
		enemy->update(frameTime, IN_MAP(man.getCenterX()), IN_MAP(man.getCenterY()));

	endTimer(false);
}

void Bomberman::ai()
{}

void Bomberman::collisions()
{
	VECTOR2 collisionVector = VECTOR2(0, 0);

	if (tileMap[IN_MAP(man.getCenterY())][IN_MAP(man.getCenterX())] == f)
	{
		man.decreaseLives();
		if (man.lives == 0)
			getLevel(false);
	}

	for (size_t i = 0; i < bonusVector.size(); i++)
	{
		if ((bonusVector[i].second.first == IN_MAP(man.getCenterY())) && (bonusVector[i].second.second == IN_MAP(man.getCenterX())))
		{
			switch (bonusVector[i].first)
			{
			case LIVE:
				man.lives++;
				bonusVector.erase(bonusVector.begin() + i);
				i--;
				break;
			case BOMB:
				numberOfBombs++;
				bonusVector.erase(bonusVector.begin() + i);
				i--;
				break;
			case EXPLOSION:
				bomb.fireWidth++;
				bonusVector.erase(bonusVector.begin() + i);
				i--;
				break;
			}
		}
	}
	
	for (size_t i = 0; i < bombs.size(); i++)
		for (auto &enemy : baseEnemies)
			if (enemy->canDestroyBomb() && enemy->collidesWith(bombs[i], collisionVector))
			{
				bombs.erase(bombs.begin() + i);
				tileMap[IN_MAP(bombs[i].getCenterY())][IN_MAP(bombs[i].getCenterX())] = __;
				i--;
				break;
			}

	if (baseEnemies.empty())
		getLevel(true);
	else
		for (size_t i = 0; i < baseEnemies.size(); i++)
		{
			if (baseEnemies[i]->collidesWith(man, collisionVector))
			{
				man.decreaseLives();
				if (man.lives == 0)
					getLevel(false);
			}
			else if (tileMap[IN_MAP(baseEnemies[i]->getCenterY())][IN_MAP(baseEnemies[i]->getCenterX())] == f)
			{
				baseEnemies.erase(baseEnemies.begin() + i);
				i--;
			}
		}
}

void Bomberman::render()
{
	graphics->spriteBegin();               

	background.draw();

	for (size_t i = 0; i < bonusVector.size(); i ++)
	{
		switch (bonusVector[i].first)
		{
		case LIVE:
			bonusheart.setY(FROM_MAP(bonusVector[i].second.first));
			bonusheart.setX(FROM_MAP(bonusVector[i].second.second));
			bonusheart.draw();
			break;
		case BOMB:
			bonusbomb.setY(FROM_MAP(bonusVector[i].second.first));
			bonusbomb.setX(FROM_MAP(bonusVector[i].second.second));
			bonusbomb.draw();
			break;
		case EXPLOSION:
			bonusexplosion.setY(FROM_MAP(bonusVector[i].second.first));
			bonusexplosion.setX(FROM_MAP(bonusVector[i].second.second));
			bonusexplosion.draw();
			break;
		}
	}

	for (int row = 0; row < MAP_HEIGHT; row++)
		for (int col = 0; col < MAP_WIDTH; col++)    
			if (tileMap[row][col] == r)
			{
				rock.setY(FROM_MAP(row));
				rock.setX(FROM_MAP(col));
				rock.draw();
			}
			else if (tileMap[row][col] == w)
			{
				wood.setY(FROM_MAP(row));
				wood.setX(FROM_MAP(col));
				wood.draw();
			}


	for (auto &_bomb : bombs)
		_bomb.draw();
	man.draw();
	for (auto &enemy : baseEnemies)
		enemy->draw();

	dxFont64->setFontColor(SETCOLOR_ARGB(255,128,128,128)); 
        dxFont64->print("Level " + std::to_string(currentLevel) , TEXTURE_SIZE, 0);
	
	bonusheart.setY(0);                                                                         
	bonusheart.setX(FROM_MAP(MAP_WIDTH - 3));													
	bonusheart.draw();																			
	dxFont64->setFontColor(SETCOLOR_ARGB(255,255,255,128)); 				
        dxFont64->print(" * " + std::to_string(man.lives) , (MAP_WIDTH - 2) * TEXTURE_SIZE, 0); 
																								
	bonusbomb.setY(0);																			
	bonusbomb.setX(FROM_MAP(MAP_WIDTH - 6));													
	bonusbomb.draw();																			
	dxFont64->setFontColor(SETCOLOR_ARGB(255,255,255,128));				
        dxFont64->print(" * " + std::to_string(numberOfBombs) , (MAP_WIDTH - 5) * TEXTURE_SIZE, 0);	
																								
	bonusexplosion.setY(0);																		
	bonusexplosion.setX(FROM_MAP(MAP_WIDTH - 9));												
	bonusexplosion.draw();																		
	dxFont64->setFontColor(SETCOLOR_ARGB(255,255,255,128)); 		
        dxFont64->print(" * " + std::to_string(bomb.fireWidth) , (MAP_WIDTH - 8) * TEXTURE_SIZE, 0);	
																							
	graphics->spriteEnd();                 
}

void Bomberman::releaseAll()
{
	SAFE_ON_LOST_DEVICE(dxFont64);
	textureManagers.onLostDevice();

	Game::releaseAll();
	return;
}

void Bomberman::endTimer(bool start)
{
	if (start || endTime > 0)
	{
		endTime++;
		if (endTime > FINAL_DELAY)
			exitGame();
	}
}

void Bomberman::resetAll()
{
	SAFE_ON_RESET_DEVICE(dxFont64);
	textureManagers.onResetDevice();
	Game::resetAll();
	return;
}
