#pragma once

#include <iostream>

#include "Entity.h"
#include "TextureManager.h"

/**
 * Interface for all components.
 */
class Component {};

// Test classes, NOT for usage 
// Note: they do not adhere to ECS principles (C should not have behaviour, for example)
class A : public Component {
	using Component::Component;
};
class B : public Component {
	using Component::Component;
};
class C : public Component {
	using Component::Component;
public:
	char c;
	inline C(char ch = 'a');
	inline const void hello() const;
};
inline C::C(char ch) {
	this->c = ch;
}
inline const void C::hello() const {
	std::cout << "Hello, " << c << std::endl;
}


class PositionComponent : public Component {
public:
	/**
	 * Construct a position component (used to position an entity on screen).
	 * 
	 * @param xPos position along x axis
	 * @param yPos position along y axis
	 * @param rotation in degrees
	 */
	PositionComponent(float x, float y, float rotation) : x(x), y(y), rotation(rotation) {}
	float x;
	float y;
	float rotation;
};

class VertexComponent : public Component {
public:
	/**
	 * Construct a vertex component (used to render vertices of an entity).
	 * 
	 * @param numVertices the number of vertices
	 * @param VBO ID of associated vertex buffer object
	 * @param VAO ID of associated vertex array object
	 */
	VertexComponent(int numVertices, unsigned int VBO, unsigned int VAO) : numVertices(numVertices), VBO(VBO), VAO(VAO) {}
	int numVertices;
	unsigned int VBO;
	unsigned int VAO;
};

class SpriteComponent : public Component {
public:
	/**
	 * Construct a sprite component (used to render texture of an entity).
	 * 
	 * @param Texture type for entity
	 * @param width of sprite
	 * @param height of sprite
	 */
	SpriteComponent(Texture texture, float width, float height) : texture(texture), width(width), height(height) {}
	Texture texture;
	float width;
	float height;
};