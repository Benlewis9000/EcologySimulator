#include "stb_image.h"

#include "TextureManager.h"

/**
 * Construct a texture manager.
 */
TextureManager::TextureManager() {

	// Initialise texture manager with these image paths
	this->init("grass-prototype.png", "lemming-prototype.png", "fox-prototype.png");

}

/**
 * Initialise the texture manager.
 * 
 * @param pathGrass path to Texture::GRASS texture 
 * @param pathLemming path to Texture::LEMMING texture image
 * @param pathFox path to Texture::FOX texture image
 */
void TextureManager::init(std::string pathGrass, std::string pathLemming, std::string pathFox) {

	// Todo: draw and add the grass and lemming textures

	//this->loadTexture(Texture::GRASS, pathGrass);
	//this->loadTexture(Texture::LEMMING, pathLemming);
	this->loadTexture(Texture::FOX, pathFox);

}

/**
 * Load an image as a texture and register the texture ID.
 * 
 * @param texture type, used as a key to access stored textures
 * @param path to image
 */
void TextureManager::loadTexture(Texture texture, std::string path) {

	// Generate texture reference and bind to context
	unsigned int ID;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	// Wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load texture image (using stb_image.h library)
	// Image attributes
	int texWidth, texHeight, texNrChannels;
	// Load image data as bytes
	unsigned char* data = stbi_load(path.c_str(), &texWidth, &texHeight, &texNrChannels, 0);
	// Check data is not null
	if (data) {

		// Generate texture from image data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		// Generate mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else {

		std::cerr << "Error: failed to load texture." << std::endl;

	}
	// Cleanup
	stbi_image_free(data);

	// Store texture ID
	this->textures[texture] = ID;

}