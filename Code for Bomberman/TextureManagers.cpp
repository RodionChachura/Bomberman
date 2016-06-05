#include "textureManagers.h"

void TextureManagers::initialize(Graphics *_graphics)
{
	graphics = _graphics;
}

void TextureManagers::add(std::string addTexture, std::string path)
{
	TextureManager* temp = new TextureManager();
	if (temp->initialize(graphics, path))
		textures.insert(std::make_pair(addTexture, temp));
	else
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing" + addTexture + "textures"));
}

void TextureManagers::onResetDevice()
{
	for (auto &texture : textures)
		texture.second->onResetDevice();
}

void TextureManagers::onLostDevice()
{
	for (auto &texture : textures)
		texture.second->onLostDevice();
}

TextureManager* TextureManagers::getTexture(std::string texture)
{
	if(textures.count(texture))
		return textures[texture];
	else
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error find texture!"));
}