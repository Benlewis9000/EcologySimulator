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
	inline unsigned int getTexture(Texture texture);
	void loadTexture(Texture texture, std::string source);

};

/**
 * Get the ID of a loaded texture.
 * 
 * @param texture to get
 */
inline unsigned int TextureManager::getTexture(Texture texture) {

	if (this->textures.find(texture) != textures.end()) {

		return this->textures[texture];

	}
	
	return NULL;
}