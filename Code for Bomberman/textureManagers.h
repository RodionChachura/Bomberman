#pragma once
#include <map>
#include <string>
#include "constants.h"
#include "graphics.h"
#include "textureManager.h"

class TextureManagers
{
private:
	std::map<std::string, TextureManager*> textures;
	Graphics *graphics;
public:

	void initialize(Graphics *_graphics);

	void add(std::string addTexture, std::string path);

	void onResetDevice();

	void onLostDevice();
	
	TextureManager* getTexture(std::string texture);

};
