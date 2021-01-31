#pragma once

#include <glad/glad.h>

#include <map>
#include <string>
#include <iostream>

enum Texture { GRASS, LEMMING, FOX };

class TextureManager {
	std::map<Texture, unsigned int> textures;

	void init(std::string pathGrass, std::string pathLemming, std::string pathFox);
public:
	TextureManager();
	unsigned int getTexture(Texture texture);
	void loadTexture(Texture texture, std::string source);

};